#include "SJF.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

SJF::SJF(const vector<Proceso>& listaProcesos) {
    procesos = listaProcesos;
}

// Ordena los procesos por tiempo de ráfaga (más corto primero)
void SJF::ordenarPorRafaga() {
    sort(procesos.begin(), procesos.end(), [](const Proceso& a, const Proceso& b) {
        return a.tiempoRafaga < b.tiempoRafaga;
    });
}

// Calcula los tiempos de ejecución, retorno y espera
void SJF::calcularTiempos() {
    int tiempoActual = 0;

    for (auto& p : procesos) {
        p.tiempoComienzo = tiempoActual;
        p.tiempoFinalizacion = p.tiempoComienzo + p.tiempoRafaga;
        p.tiempoRetorno = p.tiempoFinalizacion - p.tiempoLlegada;
        p.tiempoEspera = p.tiempoComienzo - p.tiempoLlegada;

        tiempoActual = p.tiempoFinalizacion;
    }
}

void SJF::ejecutar() {
    ordenarPorRafaga();
    calcularTiempos();
}

void SJF::mostrarResultados() const {
    cout << left << setw(10) << "Proceso"
         << setw(15) << "Llegada"
         << setw(15) << "Ráfaga"
         << setw(15) << "Comienzo"
         << setw(15) << "Final"
         << setw(15) << "Retorno"
         << setw(15) << "Espera" << endl;

    for (const auto& p : procesos) {
        cout << left << setw(10) << p.nombre
             << setw(15) << p.tiempoLlegada
             << setw(15) << p.tiempoRafaga
             << setw(15) << p.tiempoComienzo
             << setw(15) << p.tiempoFinalizacion
             << setw(15) << p.tiempoRetorno
             << setw(15) << p.tiempoEspera
             << endl;
    }

    // Calcular promedios
    double totalEspera = 0, totalRetorno = 0;
    for (const auto& p : procesos) {
        totalEspera += p.tiempoEspera;
        totalRetorno += p.tiempoRetorno;
    }

    cout << "\nTiempo promedio de espera: " << totalEspera / procesos.size() << endl;
    cout << "Tiempo promedio de retorno: " << totalRetorno / procesos.size() << endl;
}
