FROM ubuntu:20.04

ARG NUM_JOBS=8
ARG DEBIAN_FRONTEND=noninteractive

WORKDIR /app

RUN apt-get update && apt-get install -y \
        build-essential \
        autoconf \
        automake \
        libtool \
        pkg-config \
        wget \
        git \
        curl \
        vim \
        gdb \
        cmake
RUN apt-get clean

RUN cd /tmp && \
    git clone --recurse-submodules -b v1.69.0 https://github.com/grpc/grpc && \
    cd grpc && \
    mkdir -p cmake/build && \
    cd cmake/build && \
    cmake -DgRPC_INSTALL=ON \
        -DgRPC_BUILD_TESTS=OFF \
        -DCMAKE_INSTALL_PREFIX=$MY_INSTALL_DIR \
        ../.. && \
    make -j${NUM_JOBS} && \
    make install && \
    cd /app

RUN find / -name grpc_cpp_plugin 2>/dev/null

CMD protoc -I=proto/ \
    --cpp_out=src/generated/ \
    --grpc_out=src/generated/ \
    --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin \
    proto/location.proto