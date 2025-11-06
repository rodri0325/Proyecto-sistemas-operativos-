#include "cpu_interface.h"
#include "scheduler_rr.h"
#include "SJF.h"
#include <iostream>
#include <vector>
using namespace std;

void ejecutar_RR() {
    cout << "\n=== Simulación Round Robin ===\n";
    int quantum;
    cout << "Ingrese el quantum: ";
    cin >> quantum;

    SchedulerRR scheduler(quantum);

    int n;
    cout << "Ingrese el número de procesos: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        string nombre;
        int numBursts;
        cout << "\nNombre del proceso " << i + 1 << ": ";
        cin >> nombre;
        cout << "Número de ráfagas: ";
        cin >> numBursts;

        vector<int> bursts(numBursts);
        for (int j = 0; j < numBursts; ++j) {
            cout << "Duración de ráfaga " << j + 1 << ": ";
            cin >> bursts[j];
        }

        scheduler.new_process(nombre, bursts);
    }

    int ticks;
    cout << "\nIngrese el número de ticks a ejecutar: ";
    cin >> ticks;

    scheduler.run(ticks);
    cout << "\n=== Estado final ===\n";
    cout << scheduler.ps();
    scheduler.show_metrics();
}

void ejecutar_SJF() {
    cout << "\n=== Simulación SJF ===\n";
    int n;
    cout << "Ingrese el número de procesos: ";
    cin >> n;

    vector<Proceso> procesos;
    for (int i = 0; i < n; ++i) {
        Proceso p;
        cout << "\nNombre del proceso " << i + 1 << ": ";
        cin >> p.nombre;
        cout << "Tiempo de llegada: ";
        cin >> p.tiempoLlegada;
        cout << "Tiempo de ráfaga: ";
        cin >> p.tiempoRafaga;
        procesos.push_back(p);
    }

    SJF sjf(procesos);
    sjf.ejecutar();
    sjf.mostrarResultados();
}
