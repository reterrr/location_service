FROM protoc_location

WORKDIR /app

RUN apt-get update && \
    apt-get install -y libjsoncpp-dev libpqxx-dev

COPY . .

WORKDIR /build

RUN cmake /app/ && \
    make

EXPOSE 9090

CMD ["./location_service"]