#ifndef LRU_MANAGER_H
#define LRU_MANAGER_H

#include <list>
#include <unordered_map>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

class LRUManager {
private:
    int max_frames;
    int page_faults = 0;
    int total_accesses = 0;
    std::list<int> lru_list;
    std::unordered_map<int, std::list<int>::iterator> page_map;
    std::vector<int> faultHistory;

public:
    explicit LRUManager(int frames);
    void access_page(int page);
    void show_stats() const;
    void reset();
    
    int getPageFaults() const;
    const std::vector<int>& getFaultHistory() const;
};

#endif