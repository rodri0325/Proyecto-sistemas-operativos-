#include "FCFS_Disco.h"
#include <iostream>
#include <cmath>

using namespace std;

FCFS_Disco::FCFS_Disco(const vector<int>& listaPistas, int inicio)
    : peticiones(listaPistas), posicionInicial(inicio), recorridoTotal(0) {}

void FCFS_Disco::ejecutar() {
    int posicionActual = posicionInicial;

    for (int pista : peticiones) {
        recorridoTotal += abs(pista - posicionActual);
        posicionActual = pista;
        ordenAtencion.push_back(pista);
    }
}

void FCFS_Disco::mostrarResultados() const {
    cout << "Orden de atención de pistas (FCFS): ";
    for (int pista : ordenAtencion)
        cout << pista << " ";
    cout << endl;

    cout << "Recorrido total del cabezal: " << recorridoTotal << " pistas" << endl;
}

//  Función para integrarse con el CLI
void ejecutar_FCFS_Disco() {
    cout << "\n--- Simulación FCFS (Disco) ---\n";
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

    FCFS_Disco fcfs(peticiones, inicio);
    fcfs.ejecutar();
    fcfs.mostrarResultados();
}
