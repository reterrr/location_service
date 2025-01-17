cmake_minimum_required(VERSION 3.16)

project(location_service VERSION 0.0.1 LANGUAGES CXX)

# Set the C++ standard (C++11 or higher for gRPC)
set(CMAKE_CXX_STANDARD 17)


# Force finding specific Protobuf version if necessary
# You can also set specific version requirements (e.g., 3.21.7 for Protobuf)
find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)

set(_GRPC_GRPCPP gRPC::grpc++)
set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)

# Include directories for gRPC and Protobuf
include_directories(${Protobuf_INCLUDE_DIRS} ${gRPC_INCLUDE_DIRS})
include_directories(src src/generated)

# Your source files
set(SOURCES
        main.cc
        src/GrprcServer.cc
        src/GrprcServer.h
        src/generated/location.pb.h
        src/generated/location.pb.cc
        src/generated/location.grpc.pb.h
        src/generated/location.grpc.pb.cc
        src/PropertiesLoader.h
        src/Environment.h
        src/SearchLocationQueryBuilder.cpp
        src/SearchLocationQueryBuilder.h
)

# Add the executable
add_executable(location_service ${SOURCES})

# Link the necessary libraries
target_link_libraries(location_service
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF}
        ${_REFLECTION}
        -lpqxx -lpq -ljsoncpp
)