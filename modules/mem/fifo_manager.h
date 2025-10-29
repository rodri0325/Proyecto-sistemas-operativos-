#ifndef FIFO_MANAGER_H
#define FIFO_MANAGER_H

#include <queue>
#include <unordered_set>

class FIFOManager {
private:
    int max_frames;
    int page_faults = 0;
    int total_accesses = 0;
    std::queue<int> frame_queue;
    std::unordered_set<int> pages_in_memory;

public:
    explicit FIFOManager(int frames);
    void access_page(int page);
    void show_stats() const;
    void reset();
};

#endif