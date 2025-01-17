//
// Created by yhwach on 1/12/25.
//

#pragma once
#include "generated/location.grpc.pb.h"
#include <pqxx/pqxx>

class GrcServer final :
        public LocationService::Service {
public:
    GrcServer();

    grpc::Status search(grpc::ServerContext *context,
                        grpc::ServerReaderWriter<LocationsResponse,
                            SearchLocationRequest> *stream) override;

    grpc::Status getLocations(grpc::ServerContext *context, const GetLocationsRequest *request,
                              LocationsResponse *response) override;

    grpc::Status get(grpc::ServerContext *context,
                     const GetLocationRequest *request,
                     GetLocationResponse *response) override;

    static void runServer();

private:
    pqxx::connection *connection;
    pqxx::work *work;
};
