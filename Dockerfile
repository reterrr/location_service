# Use a base image with Protocol Buffers
FROM protoc_location

# Set the working directory in the container
WORKDIR /app

# Install necessary packages
RUN apt-get update && \
    apt-get install -y \
    protobuf-compiler \
    libprotobuf-dev \
    grpc++-dev \
    git \
    make \
    g++ \
    bash \
    libgrpc++-dev \
    libssl-dev \
    postgresql-client \
    autoconf \
    libtool \
    pkg-config \
    libpqxx-dev

# Clone the repository or copy your project files
# For example, if your project files are in the current directory, copy them into the container:
COPY . .

# Build the project (assuming you use cmake)
RUN mkdir -p build && cd build && cmake .. && make -j4

# Set the entry point for your application (for example, running the server)
ENTRYPOINT ["./location_service"]
