#ifndef PCB_H
#define PCB_H

#include <string>
#include <vector>

enum class ProcessState { NEW, READY, RUNNING, WAITING, TERMINATED };

class PCB {
private:
    int pid;
    std::string name;
    std::vector<int> bursts;
    ProcessState state;
    int current_burst;
    int waiting_time;
    int turnaround_time;

public:
    PCB(int pid, const std::string &name, const std::vector<int> &bursts);

    int get_pid() const;
    std::string get_name() const;
    ProcessState get_state() const;
    std::vector<int> get_bursts() const;

    void set_state(ProcessState new_state);
    bool execute_burst(int quantum);
    int get_waiting_time() const;
    int get_turnaround_time() const;

    void add_waiting_time(int time);
    void add_turnaround_time(int time);
};

#endif
