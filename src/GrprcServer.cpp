//
// Created by yhwach on 1/12/25.
//

#include "GrprcServer.h"

grpc::Status GrcServer::get(grpc::ServerContext *context,
                            const GetLocationRequest *request,
                            GetLocationResponse *response) {
    // TODO
    return grpc::Status::OK;
}

grpc::Status GrcServer::getLocations(grpc::ServerContext *context,
                                     const GetLocationsRequest *request,
                                     GetLocationsRequest *response) {
    // TODO
    return grpc::Status::OK;
}

grpc::Status GrcServer::search(grpc::ServerContext *context,
                               grpc::ServerReaderWriter<LocationsResponse,
                                   SearchLocationRequest> *stream) {

    // TODO
    return grpc::Status::OK;
}
