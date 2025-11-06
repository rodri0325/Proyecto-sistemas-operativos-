#include "PFF.h"

PFF::PFF(int numFrames, double upperThreshold, double lowerThreshold, int windowSize)
    : numFrames(numFrames), upperThreshold(upperThreshold),
      lowerThreshold(lowerThreshold), windowSize(windowSize),
      pageFaults(0), time(0) {}

void PFF::setReferenceString(const std::vector<int>& refs) {
    referenceString = refs;
}

void PFF::simulate() {
    frames.clear();
    lastUsed.clear();
    pageFaults = 0;
    time = 0;
    faultHistory.clear();

    std::vector<int> recentFaults; // tiempos recientes de fallos

    for (int page : referenceString) {
        time++;

        // Verificar si la página está en memoria
        if (frames.find(page) == frames.end()) {
            pageFaults++;
            recentFaults.push_back(time);

            // Si hay espacio libre, agregar
            if ((int)frames.size() < numFrames) {
                frames.insert(page);
            } else {
                // Reemplazo: eliminar la página menos recientemente usada (LRU)
                int lruPage = -1, oldestTime = 1e9;
                for (auto p : frames) {
                    if (lastUsed[p] < oldestTime) {
                        oldestTime = lastUsed[p];
                        lruPage = p;
                    }
                }
                frames.erase(lruPage);
                frames.insert(page);
            }
        }

        lastUsed[page] = time;

        // Eliminar fallos fuera de la ventana
        while (!recentFaults.empty() && (time - recentFaults.front() > windowSize)) {
            recentFaults.erase(recentFaults.begin());
        }

        // Calcular tasa de fallos
        double faultRate = (double)recentFaults.size() / windowSize;

        // Ajustar cantidad de marcos dinámicamente
        if (faultRate > upperThreshold) {
            numFrames++; // demasiados fallos → dar más marcos
        } else if (faultRate < lowerThreshold && numFrames > 1) {
            numFrames--; // pocos fallos → liberar marcos
        }

        // Registrar número acumulado de fallos hasta este paso
        faultHistory.push_back(pageFaults);
    }
}

int PFF::getPageFaults() const {
    return pageFaults;
}

const std::vector<int>& PFF::getFaultHistory() const {
    return faultHistory;
}
