#ifndef PFF_H
#define PFF_H

#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

class PFF {
private:
    int numFrames;          // Número actual de marcos
    double upperThreshold;  // Umbral superior de frecuencia de fallos
    double lowerThreshold;  // Umbral inferior
    int windowSize;         // Tamaño de la ventana para medir frecuencia

    std::vector<int> referenceString;          // Secuencia de referencias
    std::unordered_set<int> frames;            // Marcos actuales
    std::unordered_map<int, int> lastUsed;     // Último uso de cada página

    int pageFaults;          // Total de fallos de página
    int time;                // Contador de tiempo
    std::vector<int> faultHistory; // Registro de fallos por paso

public:
    PFF(int numFrames, double upperThreshold, double lowerThreshold, int windowSize);
    void setReferenceString(const std::vector<int>& refs);
    void simulate();

    int getPageFaults() const;
    const std::vector<int>& getFaultHistory() const;
};

#endif
