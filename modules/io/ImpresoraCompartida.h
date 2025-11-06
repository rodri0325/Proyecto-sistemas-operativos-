#ifndef IMPRESORA_COMPARTIDA_H
#define IMPRESORA_COMPARTIDA_H

#include <mutex>
#include <condition_variable>
#include <iostream>
#include <thread>
#include <chrono>

class ImpresoraCompartida {
    private:
    std::mutex mtx;
    std::condition_variable cv;
    bool disponible;

    void simularImpresion(int id);

    public:
    ImpresoraCompartida();
    void imprimir(int id);
};

#endif