FROM ubuntu
WORKDIR /app

RUN apt-get update && \
    apt-get install -y git cmake make gcc g++

RUN git clone --recurse-submodules -b v1.66.0 --depth 1 --shallow-submodules https://github.com/grpc/grpc grpc/ \
    && cd grpc/ \
    && mkdir -p cmake/build \
    && cd cmake/build \
    && cmake -DgRPC_INSTALL=ON \
          -DgRPC_BUILD_TESTS=OFF \
          -DCMAKE_INSTALL_PREFIX=/usr/local \
          ../.. \
    && make -j 4 \
    && make install \
    && cd /app \
    && rm -rf grpc

COPY . .

ENTRYPOINT protoc -I=proto/ \
    --cpp_out=generated/ \
    --grpc_out=generated/ \
    --plugin=protoc-gen-grpc=/usr/local/bin/grpc_cpp_plugin \
    proto/location.proto

