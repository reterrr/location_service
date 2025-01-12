//
// Created by yhwach on 1/12/25.
//

#pragma once
#include "../generated/location.grpc.pb.h"

class GrcServer final : public LocationService::Service {
public:
    grpc::Status search(grpc::ServerContext *context,
                        grpc::ServerReaderWriter<LocationsResponse,
                            SearchLocationRequest> *stream) override;

    grpc::Status getLocations(grpc::ServerContext *context,
                              const GetLocationsRequest *request,
                              GetLocationsRequest *response) override;

    grpc::Status get(grpc::ServerContext *context,
                     const GetLocationRequest *request,
                     GetLocationResponse *response) override;
};
