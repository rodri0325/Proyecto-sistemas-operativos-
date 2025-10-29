#include "fifo_manager.h"
#include <iostream>
#include <iomanip>

FIFOManager::FIFOManager(int frames) : max_frames(frames) {}

void FIFOManager::access_page(int page) {
    total_accesses++;
    
    // Verificar si la página ya está en memoria
    if (pages_in_memory.find(page) != pages_in_memory.end()) {
        // HIT
        std::cout << "Acceso a pagina " << page << " -> HIT" << std::endl;
    } else {
        // MISS
        page_faults++;
        std::cout << "Acceso a pagina " << page << " -> MISS" << std::endl;
        
        // Si está lleno, remover el más antiguo (FIFO)
        if (frame_queue.size() >= static_cast<size_t>(max_frames)) {
            int oldest = frame_queue.front();
            frame_queue.pop();
            pages_in_memory.erase(oldest);
            std::cout << "  Reemplazo FIFO: se elimina pagina " << oldest << std::endl;
        }
        
        // Agregar nueva página
        frame_queue.push(page);
        pages_in_memory.insert(page);
    }
    
    // Mostrar marcos actuales
    std::cout << "Marcos FIFO: [ ";
    std::queue<int> temp = frame_queue;
    while (!temp.empty()) {
        std::cout << temp.front() << " ";
        temp.pop();
    }
    std::cout << "]" << std::endl;
}

void FIFOManager::show_stats() const {
    std::cout << "\n--- Estadisticas FIFO ---" << std::endl;
    std::cout << "Accesos totales: " << total_accesses << std::endl;
    std::cout << "Fallos de pagina: " << page_faults << std::endl;
    std::cout << "Aciertos: " << (total_accesses - page_faults) << std::endl;
    
    double hit_rate = (total_accesses > 0) 
        ? (100.0 * (total_accesses - page_faults) / total_accesses) 
        : 0.0;
    std::cout << "Tasa de aciertos: " << std::fixed << std::setprecision(2) 
              << hit_rate << "%" << std::endl;
    
    // PFF (Page Fault Frequency)
    if (total_accesses > 0) {
        double pff = static_cast<double>(page_faults) / total_accesses;
        std::cout << "PFF (Page Fault Frequency): " << std::fixed 
                  << std::setprecision(4) << pff << std::endl;
    }
}

void FIFOManager::reset() {
    while (!frame_queue.empty()) frame_queue.pop();
    pages_in_memory.clear();
    page_faults = 0;
    total_accesses = 0;
    std::cout << "Memoria FIFO reiniciada." << std::endl;
}