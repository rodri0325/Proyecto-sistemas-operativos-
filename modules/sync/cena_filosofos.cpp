#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "cena_filosofos.h"

class Mesa {
private:
    std::vector<std::mutex> tenedores;
    int numFilosofos;

public:
    Mesa(int n) : numFilosofos(n), tenedores(n) {}

    void tomarTenedores(int id) {
        int izq = id;
        int der = (id + 1) % numFilosofos;

        if (id % 2 == 0) {
            tenedores[izq].lock();
            tenedores[der].lock();
        } else {
            tenedores[der].lock();
            tenedores[izq].lock();
        }
    }

    void soltarTenedores(int id) {
        int izq = id;
        int der = (id + 1) % numFilosofos;

        tenedores[izq].unlock();
        tenedores[der].unlock();
    }
};

class Filosofo {
private:
    int id;
    Mesa &mesa;
    std::thread hilo;

    void pensar() {
        std::cout << "Filosofo " << id << " está pensando\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500 + rand() % 500));
    }

    void comer() {
        std::cout << "Filosofo " << id << " empieza a comer\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(500 + rand() % 500));
        std::cout << "Filosofo " << id << " termina de comer\n";
    }

public:
    Filosofo(int id, Mesa &mesa) : id(id), mesa(mesa) {}

    void iniciar() {
        hilo = std::thread(&Filosofo::vida, this);
    }

    void vida() {
        for (int i = 0; i < 3; i++) {
            pensar();
            mesa.tomarTenedores(id);
            comer();
            mesa.soltarTenedores(id);
        }
        std::cout << "Filosofo " << id << " ha terminado su cena\n";
    }

    void esperar() {
        if (hilo.joinable())
            hilo.join();
    }
};

// 🔹 Esta función reemplaza el main()
void ejecutar_CenaFilosofos() {
    srand(time(nullptr));
    const int NUM_FILOSOFOS = 5;
    Mesa mesa(NUM_FILOSOFOS);
    std::vector<Filosofo> filosofos;

    for (int i = 0; i < NUM_FILOSOFOS; i++) {
        filosofos.emplace_back(i, mesa);
    }

    for (auto &f : filosofos) {
        f.iniciar();
    }

    for (auto &f : filosofos) {
        f.esperar();
    }

    std::cout << "\nTodos los filósofos han terminado de cenar sin interbloqueo.\n";
}