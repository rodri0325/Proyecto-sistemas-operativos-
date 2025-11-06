#include "lru_manager.h"
#include <iostream>
#include <iomanip>

LRUManager::LRUManager(int frames) : max_frames(frames) {}

void LRUManager::access_page(int page) {
    total_accesses++;
    
    auto it = page_map.find(page);
    
    if (it != page_map.end()) {
        // HIT: La página está en memoria
        std::cout << "Acceso a pagina " << page << " -> HIT" << std::endl;
        
        // Mover al frente (más recientemente usado)
        lru_list.erase(it->second);
        lru_list.push_front(page);
        page_map[page] = lru_list.begin();
    } else {
        // MISS: Fallo de página
        page_faults++;
        std::cout << "Acceso a pagina " << page << " -> MISS" << std::endl;
        
        // Si está lleno, remover el menos recientemente usado (LRU)
        if (lru_list.size() >= static_cast<size_t>(max_frames)) {
            int lru_page = lru_list.back();
            lru_list.pop_back();
            page_map.erase(lru_page);
            std::cout << "  Reemplazo LRU: se elimina pagina " << lru_page << std::endl;
        }
        
        // Agregar nueva página al frente
        lru_list.push_front(page);
        page_map[page] = lru_list.begin();
    }
    
    // Registrar número acumulado de fallos
    faultHistory.push_back(page_faults);
    
    // Mostrar marcos actuales (del más reciente al menos reciente)
    std::cout << "Marcos LRU: [ ";
    for (int p : lru_list) {
        std::cout << p << " ";
    }
    std::cout << "]" << std::endl;
}

void LRUManager::show_stats() const {
    std::cout << "\n--- Estadisticas LRU ---" << std::endl;
    std::cout << "Tamaño de marcos: " << max_frames << std::endl;
    std::cout << "Accesos totales: " << total_accesses << std::endl;
    std::cout << "Fallos de pagina: " << page_faults << std::endl;
    std::cout << "Aciertos: " << (total_accesses - page_faults) << std::endl;
    
    double hit_rate = (total_accesses > 0)
        ? (100.0 * (total_accesses - page_faults) / total_accesses)
        : 0.0;
    std::cout << "Tasa de aciertos: " << std::fixed << std::setprecision(2)
              << hit_rate << "%" << std::endl;
    
    if (total_accesses > 0) {
        double pff = static_cast<double>(page_faults) / total_accesses;
        std::cout << "PFF (Page Fault Frequency): " << std::fixed
                  << std::setprecision(4) << pff << std::endl;
    }
}

void LRUManager::reset() {
    lru_list.clear();
    page_map.clear();
    faultHistory.clear();
    page_faults = 0;
    total_accesses = 0;
    std::cout << "Memoria LRU reiniciada." << std::endl;
}

int LRUManager::getPageFaults() const {
    return page_faults;
}

const std::vector<int>& LRUManager::getFaultHistory() const {
    return faultHistory;
}