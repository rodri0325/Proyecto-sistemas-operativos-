#ifndef FCFS_DISCO_H
#define FCFS_DISCO_H

#include <vector>

class FCFS_Disco {
private:
    std::vector<int> peticiones;
    int posicionInicial;
    std::vector<int> ordenAtencion;
    int recorridoTotal;

public:
    FCFS_Disco(const std::vector<int>& listaPistas, int inicio);
    void ejecutar();
    void mostrarResultados() const;

    int getRecorridoTotal() const { return recorridoTotal; }
    std::vector<int> getOrdenAtencion() const { return ordenAtencion; }
};

// función global que usará el CLI
void ejecutar_FCFS_Disco();

#endif
