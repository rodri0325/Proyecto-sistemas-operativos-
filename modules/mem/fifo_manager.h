#ifndef FIFO_MANAGER_H
#define FIFO_MANAGER_H

#include <queue>
#include <unordered_set>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

struct FifoStats {
    int frame_size;
    int page_faults;
    int total_accesses;
};

class FIFOManager {
private:
    int max_frames;
    int page_faults = 0;
    int total_accesses = 0;
    std::queue<int> frame_queue;
    std::unordered_set<int> pages_in_memory;
    std::vector<int> faultHistory; // Historial de fallos por paso
    std::vector<FifoStats> stats_history;

public:
    explicit FIFOManager(int frames);
    void access_page(int page);
    void show_stats() const;
    void reset();

    // Métodos para graficar
    int getPageFaults() const;
    const std::vector<int>& getFaultHistory() const;
    void save_stats();
    const std::vector<FifoStats>& get_stats() const;
};

#endif