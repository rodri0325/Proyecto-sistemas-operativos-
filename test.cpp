#include <iostream>
#include <chrono>
#include <thread>
int main() {
    std::cout << "Probando entorno C++...\n";
    std::cout.flush(); // fuerza a imprimir inmediatamente
    std::this_thread::sleep_for(std::chrono::seconds(3)); // espera 3 segundos
    return 0;
}
