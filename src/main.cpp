#include "../include/Server.hpp"

int main(){
    int port=8080;
    int numThreads=4;

    Server server(port,numThreads);
    server.start();

    return 0;
}