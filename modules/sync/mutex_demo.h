#ifndef MUTEX_DEMO_H
#define MUTEX_DEMO_H

#include <thread>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <iostream>
#include <chrono>

class ProducerConsumer {
private:
    std::queue<int> buffer;
    const unsigned int max_size;
    std::mutex mtx;
    std::condition_variable cv_producer, cv_consumer;
    bool finished = false;

public:
    ProducerConsumer(unsigned int size);
    void producer(int id, int count);
    void consumer(int id);
    void run();
};

#endif
