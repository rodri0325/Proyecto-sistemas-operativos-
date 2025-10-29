#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>

std::mutex mtx;
std::queue<int> buffer;
const unsigned int MAX_BUFFER = 5;
bool running = true;

void productor() {
    int item = 0;
    while (item < 10) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
        std::unique_lock<std::mutex> lock(mtx);
        if (buffer.size() < MAX_BUFFER) {
            buffer.push(++item);
            std::cout << "[Productor] produjo item " << item << std::endl;
        }
    }
}

void consumidor() {
    while (running) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        std::unique_lock<std::mutex> lock(mtx);
        if (!buffer.empty()) {
            int item = buffer.front();
            buffer.pop();
            std::cout << "    [Consumidor] consumio item " << item << std::endl;
        } else if (!running) break;
    }
}

void run_mutex_demo() {
    std::cout << "Iniciando problema Productor-Consumidor (mutex)...\n";

    std::thread prod(productor);
    std::thread cons(consumidor);

    prod.join();
    running = false;
    cons.join();

    std::cout << "Finalizo Productor-Consumidor.\n";
}
