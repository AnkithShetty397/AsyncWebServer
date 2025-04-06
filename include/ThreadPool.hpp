#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

class ThreadPool{
private: 
    vector<thread> workers;
    queue<int>& clientQueue;
    mutex& queueMutex;
    condition_variable& queueCondition;
    bool stopThreads;

public:
    ThreadPool(int numThreads,queue<int>& q, mutex& mtx,condition_variable& cv);
    void start();
    void workerLoop();
    void stop();
};

#endif
