#include "../include/ThreadPool.hpp"

ThreadPool::ThreadPool(int numThreads,queue<int>& q,mutex& mtx,condition_variable& cv)
    : clientQueue(q), queueMutex(mtx), queueCondition(cv), stopThreads(false){
    for(int i=0;i<numThreads;i++){
        workers.emplace_back(&ThreadPool::workerLoop,this);
    }
}

void ThreadPool::start(){
    cout<<"Thread pool started..."<<endl;
}

void ThreadPool::workerLoop(){
    while(!stopThreads){
        int clientSocket;
        {
            unique_lock<mutex> lock(queueMutex);
            queueCondition.wait(lock,[this]{ return !clientQueue.empty() || stopThreads; });

            if(stopThreads) break;

            clientSocket = clientQueue.front();
            clientQueue.pop();

            cout<<"Thread "<<this_thread::get_id()<<" picked socket"<<clientSocket<<endl;
        }

        //process the request
    }
}

void ThreadPool::stop(){
    stopThreads = true;
    queueCondition.notify_all();
    for(auto& worker: workers){
        if(worker.joinable()) worker.join();
    }
}