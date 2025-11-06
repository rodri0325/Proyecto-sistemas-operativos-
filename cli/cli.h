#ifndef CLI_H
#define CLI_H

#include <iostream>
using namespace std;

class CLI {
public:
    void iniciar();  // Inicia el menú principal

private:
    // Submenús
    void menuCPU();
    void menuDisco();
    void menuMemoria();
    void menuIO();
    void menuSync();

    // Utilidades
    void limpiarPantalla();
    void pausar();
};

#endif
