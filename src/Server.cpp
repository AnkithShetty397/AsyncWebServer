#include "../include/Server.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

Server::Server(int port,int numThreads): threadPool(numThreads,clientQueue,queueMutex,queueCondition){
    server_socket = createSocket(port);
}

int Server::createSocket(int port){
    int sock = socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in serverAddr{};

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(sock,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(sock,10);

    return sock;
}

void Server::start(){
    cout<<"Started server..."<<endl;
    threadPool.start();
    acceptConnections();
}

void Server::acceptConnections(){
    while(true){
        int clientSocket = accept(server_socket,NULL,NULL);
        unique_lock<mutex> lock(queueMutex);
        clientQueue.push(clientSocket);
        queueCondition.notify_one();

        cout<<"Request from socket: "<<clientSocket<<endl;
    }
}

void Server::stop(){
    close(server_socket);
    threadPool.stop();
}