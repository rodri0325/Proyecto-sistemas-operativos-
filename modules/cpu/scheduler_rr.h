#ifndef SCHEDULER_RR_H
#define SCHEDULER_RR_H

#include "pcb.h"
#include <queue>
#include <memory>
#include <string>
#include <map>
#include <iomanip>
#include <cmath>

class SchedulerRR {
private:
    int quantum;
    std::queue<std::shared_ptr<PCB>> ready_queue;
    std::shared_ptr<PCB> current_process;
    int tick_count;
    int pid_counter;
    std::map<int, std::shared_ptr<PCB>> all_processes;

public:
    SchedulerRR(int q);

    std::shared_ptr<PCB> new_process(const std::string &name, const std::vector<int> &bursts);
    void new_process(std::shared_ptr<PCB> process);
    void run(int ticks);
    std::string ps() const;
    std::map<int, std::pair<int, int>> collect_metrics();
    void tick();
    void kill_process(int pid);
    void show_metrics() const;
};

#endif
