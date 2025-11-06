#ifndef SSTF_H
#define SSTF_H

#include <vector>

struct Peticion {
    int pista;
    int distancia;
    bool atendida;
};

class SSTF {
private:
    std::vector<Peticion> peticiones;
    int posicionInicial;
    std::vector<int> ordenAtencion;
    int recorridoTotal;

    int buscarMasCercana(int posicionActual);
    void calcularRecorrido();

public:
    SSTF(const std::vector<int>& listaPistas, int inicio);
    void ejecutar();
    void mostrarResultados() const;

    int getRecorridoTotal() const;
    std::vector<int> getOrdenAtencion() const;
};

// Declaramos la función global que usará el CLI
void ejecutar_SSTF();

#endif
