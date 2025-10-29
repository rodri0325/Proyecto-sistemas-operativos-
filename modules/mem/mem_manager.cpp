#include "mem_manager.h"
#include <iostream>
#include <algorithm>

MemManager::MemManager(int frames) : max_frames(frames) {}

void MemManager::access_page(int page) {
    total_accesses++;
    auto it = std::find(pages.begin(), pages.end(), page);

    if (it == pages.end()) {
        page_faults++;
        std::cout << "Acceso a pagina " << page << " -> MISS" << std::endl;

        if (pages.size() == max_frames) {
            int removed = pages.back();
            pages.pop_back();
            std::cout << "Reemplazo: se elimina pagina " << removed << std::endl;
        }
    } else {
        std::cout << "Acceso a pagina " << page << " -> HIT" << std::endl;
        pages.erase(it);
    }

    // Insertar al frente (mas reciente)
    pages.insert(pages.begin(), page);
    mostrar_marcos();
}

void MemManager::mostrar_marcos() const {
    std::cout << "Marcos actuales (mas reciente - menos reciente): [ ";
    for (int p : pages) std::cout << p << " ";
    std::cout << "]" << std::endl;
}

void MemManager::show_stats() const {
    std::cout << "\n--- Estadisticas LRU ---" << std::endl;
    std::cout << "Accesos totales: " << total_accesses << std::endl;
    std::cout << "Fallos de pagina: " << page_faults << std::endl;
    std::cout << "Aciertos: " << total_accesses - page_faults << std::endl;
    double hit_rate = (total_accesses > 0)
                        ? (100.0 * (total_accesses - page_faults) / total_accesses)
                        : 0.0;
    std::cout << "Tasa de aciertos: " << hit_rate << "%" << std::endl;
}
