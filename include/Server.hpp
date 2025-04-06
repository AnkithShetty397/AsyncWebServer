#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <queue>
#include <mutex>
#include <condition_variable>
#include "ThreadPool.hpp"

using namespace std;

class Server{
private:
    int server_socket;
    queue<int> clientQueue;
    mutex queueMutex;
    condition_variable queueCondition;
    ThreadPool threadPool;
public:
    Server(int port,int numThreads);
    void start();
    void stop();
    void acceptConnections();
    int createSocket(int port);
};

#endif