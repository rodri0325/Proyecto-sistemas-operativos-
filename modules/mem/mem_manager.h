#ifndef MEM_MANAGER_H
#define MEM_MANAGER_H

#include <vector>

class MemManager {
private:
    int max_frames;            // Numero maximo de marcos
    int page_faults = 0;       // Contador de fallos de pagina
    int total_accesses = 0;    // Contador total de accesos
    std::vector<int> pages;    // Paginas cargadas actualmente

    void mostrar_marcos() const; // Muestra el estado de los marcos

public:
    explicit MemManager(int frames);
    void access_page(int page); // Simula el acceso a una pagina
    void show_stats() const;    // Muestra estadisticas LRU
};

#endif
