#include "SSTF.h"
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

SSTF::SSTF(const vector<int>& listaPistas, int inicio) {
    posicionInicial = inicio;
    recorridoTotal = 0;

    for (int pista : listaPistas)
        peticiones.push_back({pista, 0, false});
}

int SSTF::buscarMasCercana(int posicionActual) {
    int indice = -1;
    int distanciaMin = numeric_limits<int>::max();

    for (int i = 0; i < (int)peticiones.size(); i++) {
        if (!peticiones[i].atendida) {
            int dist = abs(peticiones[i].pista - posicionActual);
            if (dist < distanciaMin) {
                distanciaMin = dist;
                indice = i;
            }
        }
    }
    return indice;
}

void SSTF::calcularRecorrido() {
    int posicionActual = posicionInicial;

    for (size_t i = 0; i < peticiones.size(); i++) {
        int indice = buscarMasCercana(posicionActual);
        if (indice == -1) break;

        int movimiento = abs(peticiones[indice].pista - posicionActual);
        recorridoTotal += movimiento;
        posicionActual = peticiones[indice].pista;
        peticiones[indice].atendida = true;
        ordenAtencion.push_back(posicionActual);
    }
}

void SSTF::ejecutar() {
    calcularRecorrido();
}

void SSTF::mostrarResultados() const {
    cout << "Orden de atención de pistas (SSTF): ";
    for (int pista : ordenAtencion)
        cout << pista << " ";
    cout << endl;

    cout << "Recorrido total del cabezal: " << recorridoTotal << " pistas" << endl;
}

int SSTF::getRecorridoTotal() const { return recorridoTotal; }
vector<int> SSTF::getOrdenAtencion() const { return ordenAtencion; }

// Función para integrarse con el CLI
void ejecutar_SSTF() {
    cout << "\n--- Simulación SSTF (Disco) ---\n";
    int inicio;
    cout << "Ingrese la posición inicial del cabezal: ";
    cin >> inicio;

    int n;
    cout << "Ingrese el número de peticiones: ";
    cin >> n;

    vector<int> peticiones(n);
    cout << "Ingrese las pistas solicitadas:\n";
    for (int i = 0; i < n; ++i)
        cin >> peticiones[i];

    SSTF sstf(peticiones, inicio);
    sstf.ejecutar();
    sstf.mostrarResultados();
}
