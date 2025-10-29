#include "pcb.h"

PCB::PCB(int pid, const std::string &name, const std::vector<int> &bursts)
    : pid(pid), name(name), bursts(bursts), state(ProcessState::NEW),
      current_burst(0), waiting_time(0), turnaround_time(0) {}

int PCB::get_pid() const { return pid; }
std::string PCB::get_name() const { return name; }
ProcessState PCB::get_state() const { return state; }
std::vector<int> PCB::get_bursts() const { return bursts; }

void PCB::set_state(ProcessState new_state) { state = new_state; }

bool PCB::execute_burst(int quantum) {
    if (current_burst >= (int)bursts.size())
        return true;

    if (bursts[current_burst] > quantum) {
        bursts[current_burst] -= quantum;
        return false;
    } else {
        bursts[current_burst] = 0;
        current_burst++;
        return current_burst >= (int)bursts.size();
    }
}

int PCB::get_waiting_time() const { return waiting_time; }
int PCB::get_turnaround_time() const { return turnaround_time; }

void PCB::add_waiting_time(int time) { waiting_time += time; }
void PCB::add_turnaround_time(int time) { turnaround_time += time; }
