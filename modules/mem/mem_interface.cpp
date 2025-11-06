#include "mem_interface.h"
#include "fifo_manager.h"
#include "PFF.h"
#include <iostream>
#include <vector>
using namespace std;

// ------------------ FIFO ------------------
void ejecutar_FIFO() {
    cout << "\n=== Simulación FIFO ===\n";
    int frames;
    cout << "Ingrese el número de marcos: ";
    cin >> frames;

    FIFOManager fifo(frames);

    int n;
    cout << "Ingrese la cantidad de accesos a páginas: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int page;
        cout << "Página #" << i + 1 << ": ";
        cin >> page;
        fifo.access_page(page);
    }

    fifo.show_stats();
    fifo.reset();
}

// ------------------ LRU (Simulado, o segunda versión FIFO) ------------------
void ejecutar_LRU() {
    cout << "\n=== Simulación LRU ===\n";
    int frames;
    cout << "Ingrese el número de marcos: ";
    cin >> frames;

    FIFOManager lru(frames); // si luego haces clase LRUManager, cámbialo

    int n;
    cout << "Ingrese la cantidad de accesos a páginas: ";
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int page;
        cout << "Página #" << i + 1 << ": ";
        cin >> page;
        lru.access_page(page);
    }

    lru.show_stats();
    lru.reset();
}

// ------------------ PFF ------------------
void ejecutar_PFF() {
    cout << "\n=== Simulación PFF (Page Fault Frequency) ===\n";
    int frames, window;
    double upper, lower;

    cout << "Número inicial de marcos: ";
    cin >> frames;
    cout << "Umbral superior (por ejemplo 0.5): ";
    cin >> upper;
    cout << "Umbral inferior (por ejemplo 0.1): ";
    cin >> lower;
    cout << "Tamaño de ventana: ";
    cin >> window;

    PFF pff(frames, upper, lower, window);

    int n;
    cout << "Ingrese la longitud de la secuencia de referencias: ";
    cin >> n;

    vector<int> refs(n);
    for (int i = 0; i < n; ++i) {
        cout << "Referencia #" << i + 1 << ": ";
        cin >> refs[i];
    }

    pff.setReferenceString(refs);
    pff.simulate();

    cout << "\n--- Resultados PFF ---\n";
    cout << "Total de fallos de página: " << pff.getPageFaults() << endl;

    const auto& hist = pff.getFaultHistory();
    cout << "Historial de fallos acumulados: ";
    for (int f : hist) cout << f << " ";
    cout << endl;
}
