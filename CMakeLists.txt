cmake_minimum_required(VERSION 3.28)

project(location_service)

# Set the C++ standard (C++11 or higher for gRPC)
set(CMAKE_CXX_STANDARD 17)


# Force finding specific Protobuf version if necessary
# You can also set specific version requirements (e.g., 3.21.7 for Protobuf)
find_package(Protobuf REQUIRED CONFIG)
find_package(gRPC REQUIRED CONFIG)

# Include directories for gRPC and Protobuf
include_directories(${Protobuf_INCLUDE_DIRS} ${gRPC_INCLUDE_DIRS})
include_directories(src)

# Your source files
set(SOURCES
        main.cpp
        src/GrprcServer.cpp
        src/GrprcServer.h
)

# Add the executable
add_executable(location_service ${SOURCES})

# Link the necessary libraries
target_link_libraries(location_service
        ${Protobuf_LIBRARIES}
        ${gRPC_LIBRARIES}
)
