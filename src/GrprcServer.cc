//
// Created by yhwach on 1/12/25.
//

#include "GrprcServer.h"

#include "Environment.h"
#include <grpcpp/server_builder.h>

#include "SearchLocationQueryBuilder.h"

grpc::Status GrcServer::get(grpc::ServerContext *context,
                            const GetLocationRequest *request,
                            GetLocationResponse *response) {
    uint64_t id = request->id();
    auto result = work->exec("SELECT * FROM cities WHERE id = " + std::to_string(id));
    work->commit();

    if (result.empty()) {
        return {grpc::StatusCode::NOT_FOUND, "Location not found"};
    }

    const auto &row = result[0];

    auto location = new Location();

    location->set_id(id);
    location->set_country(row["country"].as<std::string>());
    location->set_name(row["name"].as<std::string>());
    location->set_latitude(row["lat"].as<double>());
    location->set_longitude(row["lon"].as<double>());

    response->set_allocated_location(location);

    return grpc::Status::OK;
}

void GrcServer::runServer() {
    std::string server_address(Environment::value["server"]["address"].asString());
    GrcServer service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
}

grpc::Status GrcServer::getLocations(grpc::ServerContext *context,
                                     const GetLocationsRequest *request,
                                     LocationsResponse *response) {
    const auto &ids = request->ids();

    std::string idString;
    idString += "(";

    for (int i = 0; i < ids.size(); i++) {
        idString += std::to_string(ids[i]);

        if (i != ids.size() - 1)
            idString += ", ";
    }

    idString += ")";

    auto rows = work->exec("select * from cities where id in" + idString);

    for (const auto &row: rows) {
        auto location = response->add_locations();
        location->set_id(row["id"].as<uint64_t>());
        location->set_country(row["country"].as<std::string>());
        location->set_name(row["name"].as<std::string>());
        location->set_latitude(row["lat"].as<double>());
        location->set_longitude(row["lon"].as<double>());
    }

    return grpc::Status::OK;
}

GrcServer::GrcServer() {
    connection = new pqxx::connection(Environment::value["db"]["connection-string"].asString());
    work = new pqxx::work(*connection);
}

grpc::Status GrcServer::search(grpc::ServerContext *context,
                               grpc::ServerReaderWriter<LocationsResponse,
                                   SearchLocationRequest> *stream) {
    SearchLocationRequest request;
    while (stream->Read(&request)) {
        const auto &name = request.pattern_name();
        const auto &country = request.pattern_country();
        double lat = request.pattern_latitude();
        double lon = request.pattern_longitude();

       auto builder = SearchLocationQueryBuilder(name, country, lat, lon);

        auto rows =
                work->exec(builder.build());

        LocationsResponse response;
        for (const auto &row: rows) {
            auto location = response.add_locations();
            location->set_id(row["id"].as<uint64_t>());
            location->set_country(row["country"].as<std::string>());
            location->set_name(row["name"].as<std::string>());
            location->set_latitude(row["lat"].as<double>());
            location->set_longitude(row["lon"].as<double>());
        }

        stream->Write(response);
    }

    return grpc::Status::OK;
}
