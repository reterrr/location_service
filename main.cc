#include "Environment.h"
#include "src/GrprcServer.h"
#include "src/PropertiesLoader.h"

int main() {
    PropertiesLoader<Environment>::load("/app/properties.json");
    GrcServer::runServer();

    return 0;
}
