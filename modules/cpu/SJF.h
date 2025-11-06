#ifndef SJF_H
#define SJF_H

#include <vector>
#include <string>

struct Proceso {
    std::string nombre;
    int tiempoLlegada;
    int tiempoRafaga;
    int tiempoComienzo;
    int tiempoFinalizacion;
    int tiempoRetorno;
    int tiempoEspera;
};

class SJF {
private:
    std::vector<Proceso> procesos;
    void ordenarPorRafaga();
    void calcularTiempos();

public:
    SJF(const std::vector<Proceso>& listaProcesos);
    void ejecutar();
    void mostrarResultados() const;
};

#endif
