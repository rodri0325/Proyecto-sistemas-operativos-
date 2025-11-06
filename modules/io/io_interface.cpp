#include "io_interface.h"
#include "ImpresoraCompartida.h"
#include <iostream>
#include <thread>
#include <vector>

void ejecutar_ImpresoraCompartida() {
    std::cout << "\n=== Simulación de Impresora Compartida ===\n";

    int numEmpleados;
    std::cout << "Ingrese el número de empleados (hilos): ";
    std::cin >> numEmpleados;

    ImpresoraCompartida impresora;
    std::vector<std::thread> empleados;

    // Crear hilos de empleados
    for (int i = 0; i < numEmpleados; ++i) {
        empleados.emplace_back([&impresora, i]() {
            impresora.imprimir(i + 1);
        });
    }

    // Esperar a que todos terminen
    for (auto &t : empleados) {
        if (t.joinable()) t.join();
    }

    std::cout << "\nSimulación finalizada. Todos los empleados imprimieron correctamente.\n";
}