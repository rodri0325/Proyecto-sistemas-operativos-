#include "ImpresoraCompartida.h"
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <chrono>
#include <random>

ImpresoraCompartida::ImpresoraCompartida() : disponible(true) {}

void ImpresoraCompartida::simularImpresion(int id) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(1000, 3000);

    std::this_thread::sleep_for(std::chrono::milliseconds(dis(gen)));
}

void ImpresoraCompartida::imprimir(int id) {
    std::unique_lock<std::mutex> lock(mtx);

    std::cout << "Empleado " << id << " esperando para imprimir" << std::endl;
    cv.wait(lock, [this]() { return disponible; });

    disponible = false;
    std::cout << "Empleado " << id << " esta imprimiendo" << std::endl;
    lock.unlock();

    simularImpresion(id);

    lock.lock();
    disponible = true;
    std::cout << "Empleado " << id << " terminp de imprimir." << std::endl;
    lock.unlock();

    cv.notify_one();
}