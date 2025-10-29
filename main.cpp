#include <iostream>
#include "modules/cpu/scheduler_rr.h"
#include "modules/mem/mem_manager.h"
#include "modules/mem/fifo_manager.h"

int main() {
    std::cout << "\n" << std::endl;
    std::cout << "   SIMULADOR DE SISTEMA OPERATIVO v1.0    " << std::endl;
    std::cout << "        PRUEBA AUTOMATICA                 " << std::endl;
    std::cout << "═══════════════════════════════════════\n" << std::endl;
    
    // ===== PRUEBA 1: PLANIFICADOR ROUND ROBIN =====
    std::cout << "\n========================================" << std::endl;
    std::cout << "  PRUEBA 1: PLANIFICADOR ROUND ROBIN" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    SchedulerRR scheduler(2); // Quantum = 2
    
    std::cout << "Creando 3 procesos..." << std::endl;
    auto p1 = scheduler.new_process("P1", {5});
    auto p2 = scheduler.new_process("P2", {3});
    auto p3 = scheduler.new_process("P3", {8});
    
    std::cout << "\n--- Estado inicial ---" << std::endl;
    std::cout << scheduler.ps() << std::endl;
    
    std::cout << "Ejecutando 20 ticks..." << std::endl;
    scheduler.run(20);
    
    std::cout << "\n--- Estado final ---" << std::endl;
    std::cout << scheduler.ps() << std::endl;
    
    std::cout << "\n--- Metricas ---" << std::endl;
    scheduler.show_metrics();
    
    // ===== PRUEBA 2: MEMORIA CON FIFO =====
    std::cout << "\n\n========================================" << std::endl;
    std::cout << "  PRUEBA 2: GESTION DE MEMORIA (FIFO)" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    FIFOManager fifo(3); // 3 marcos
    
    std::cout << "Simulando accesos a paginas: 1, 2, 3, 4, 1, 2, 5, 1, 2, 3\n" << std::endl;
    
    int sequence[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3};
    for (int page : sequence) {
        fifo.access_page(page);
        std::cout << std::endl;
    }
    
    fifo.show_stats();
    
    // ===== PRUEBA 3: MEMORIA CON LRU =====
    std::cout << "\n\n========================================" << std::endl;
    std::cout << "  PRUEBA 3: GESTION DE MEMORIA (LRU)" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    MemManager lru(3); // 3 marcos
    
    std::cout << "Simulando accesos a paginas: 1, 2, 3, 4, 1, 2, 5, 1, 2, 3\n" << std::endl;
    
    for (int page : sequence) {
        lru.access_page(page);
        std::cout << std::endl;
    }
    
    lru.show_stats();
    
    // ===== PRUEBA 4: COMANDOS INDIVIDUALES =====
    std::cout << "\n\n========================================" << std::endl;
    std::cout << "  PRUEBA 4: COMANDOS INDIVIDUALES" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    SchedulerRR scheduler2(2);
    
    std::cout << "\nComando: new 5" << std::endl;
    scheduler2.new_process("Proc1", {5});
    
    std::cout << "\nComando: new 3" << std::endl;
    scheduler2.new_process("Proc2", {3});
    
    std::cout << "\nComando: ps" << std::endl;
    std::cout << scheduler2.ps();
    
    std::cout << "\nComando: run 5" << std::endl;
    scheduler2.run(5);
    
    std::cout << "\nComando: ps" << std::endl;
    std::cout << scheduler2.ps();
    
    std::cout << "\nComando: metrics" << std::endl;
    scheduler2.show_metrics();
    
    std::cout << "\nComando: kill 1" << std::endl;
    scheduler2.kill_process(1);
    
    std::cout << "\nComando: ps" << std::endl;
    std::cout << scheduler2.ps();
    
    // ===== FIN =====
    std::cout << "\n\n========================================" << std::endl;
    std::cout << "     TODAS LAS PRUEBAS COMPLETADAS" << std::endl;
    std::cout << "========================================\n" << std::endl;
    
    std::cout << "Presione ENTER para salir..." << std::endl;
    std::cin.get();
    
    return 0;
}