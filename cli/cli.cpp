#include "CLI.h"

// ============================================================
//              IMPORTACIÓN DE MÓDULOS
// ============================================================

#include "../modules/cpu/cpu_interface.h"   
#include "../modules/cpu/SJF.h"
#include "../modules/cpu/scheduler_rr.h"

#include "../modules/disk/FCFS_Disco.h"
#include "../modules/disk/SSTF.h"

#include "../modules/mem/fifo_manager.h"
#include "../modules/mem/lru_manager.h"
#include "../modules/mem/pff.h"
#include "../modules/mem/mem_interface.h"

#include "../modules/io/ImpresoraCompartida.h"
#include "../modules/io/io_interface.h"

#include "../modules/sync/cena_filosofos.h"


// ============================================================
//              MENÚ PRINCIPAL
// ============================================================
void CLI::iniciar() {
    int opcion = -1;

    do {
        limpiarPantalla();
        std::cout << "==============================\n";
        std::cout << "   SIMULADOR DE KERNEL OS\n";
        std::cout << "==============================\n";
        std::cout << "1. CPU Scheduling\n";
        std::cout << "2. Planificación de Disco\n";
        std::cout << "3. Gestión de Memoria\n";
        std::cout << "4. Entrada/Salida (I/O)\n";
        std::cout << "5. Sincronización\n";
        std::cout << "0. Salir\n";
        std::cout << "==============================\n";
        std::cout << "Seleccione un módulo: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1: menuCPU(); break;
            case 2: menuDisco(); break;
            case 3: menuMemoria(); break;
            case 4: menuIO(); break;
            case 5: menuSync(); break;
            case 0: std::cout << "Saliendo del sistema...\n"; break;
            default:
                std::cout << "Opción inválida.\n";
                pausar();
        }
    } while (opcion != 0);
}

// ============================================================
//              SUBMENÚS DE CADA MÓDULO
// ============================================================

// ---------- CPU ----------
void CLI::menuCPU() {
    int op;
    limpiarPantalla();
    std::cout << "=== Módulo CPU ===\n";
    std::cout << "1. Round Robin (RR)\n";
    std::cout << "2. Shortest Job First (SJF)\n";
    std::cout << "0. Volver\n";
    std::cout << "Seleccione algoritmo: ";
    std::cin >> op;

    switch (op) {
        case 1: ejecutar_RR(); break;   // 🔹 Llama a cpu_interface.cpp
        case 2: ejecutar_SJF(); break;  // 🔹 Llama a cpu_interface.cpp
        default: break;
    }
    pausar();
}

// ---------- Disco ----------
void CLI::menuDisco() {
    int op;
    limpiarPantalla();
    std::cout << "=== Módulo Disco ===\n";
    std::cout << "1. FCFS\n";
    std::cout << "2. SSTF\n";
    std::cout << "0. Volver\n";
    std::cout << "Seleccione algoritmo: ";
    std::cin >> op;

    switch (op) {
        case 1: ejecutar_FCFS_Disco(); break;
        case 2: ejecutar_SSTF(); break;
        default: break;
    }
    pausar();
}

// ---------- Memoria ----------
void CLI::menuMemoria() {
    int opcion;
    do {
        limpiarPantalla();
        std::cout << "\n=== Módulo de Memoria ===" << std::endl;
        std::cout << "1. FIFO" << std::endl;
        std::cout << "2. LRU" << std::endl;
        std::cout << "3. PFF" << std::endl;
        std::cout << "0. Volver al menú principal" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                ejecutar_FIFO();
                break;
            case 2:
                ejecutar_LRU();
                break;
            case 3:
                ejecutar_PFF();
                break;
            case 0:
                std::cout << "Volviendo al menú principal..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida." << std::endl;
                break;
        }

        if (opcion != 0) pausar();
    } while (opcion != 0);
}

// ---------- I/O ----------
void CLI::menuIO() {
    int opcion;
    do {
        limpiarPantalla();
        std::cout << "\n=== Módulo de Entrada/Salida ===" << std::endl;
        std::cout << "1. Impresora Compartida" << std::endl;
        std::cout << "0. Volver al menú principal" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                ejecutar_ImpresoraCompartida();
                break;
            case 0:
                std::cout << "Volviendo al menú principal..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida." << std::endl;
                break;
        }

        if (opcion != 0) pausar();
    } while (opcion != 0);
}



// ---------- Sincronización ----------
void CLI::menuSync() {
    int opcion;
    do {
        limpiarPantalla();
        std::cout << "\n=== Módulo de Sincronización ===" << std::endl;
        std::cout << "1. Problema de los Filósofos Comensales" << std::endl;
        std::cout << "0. Volver al menú principal" << std::endl;
        std::cout << "Seleccione una opción: ";
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                ejecutar_CenaFilosofos();
                break;
            case 0:
                std::cout << "Volviendo al menú principal..." << std::endl;
                break;
            default:
                std::cout << "Opción inválida." << std::endl;
                break;
        }

        if (opcion != 0) pausar();
    } while (opcion != 0);
}


// ============================================================
//              FUNCIONES AUXILIARES
// ============================================================
void CLI::limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void CLI::pausar() {
    std::cout << "\nPresione ENTER para continuar...";
    std::cin.ignore();
    std::cin.get();
}