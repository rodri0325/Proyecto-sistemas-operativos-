#include "scheduler_rr.h"
#include <iostream>
#include <sstream>
#include <cmath>

SchedulerRR::SchedulerRR(int q) : quantum(q), tick_count(0), pid_counter(1) {}

std::shared_ptr<PCB> SchedulerRR::new_process(const std::string &name, const std::vector<int> &bursts) {
    auto pcb = std::make_shared<PCB>(pid_counter++, name, bursts);
    pcb->set_state(ProcessState::READY);
    ready_queue.push(pcb);
    all_processes[pcb->get_pid()] = pcb;
    return pcb;
}

void SchedulerRR::new_process(std::shared_ptr<PCB> process) {
    process->set_state(ProcessState::READY);
    ready_queue.push(process);
    all_processes[process->get_pid()] = process;
}

void SchedulerRR::run(int ticks) {
    for (int i = 0; i < ticks; ++i) {
        if (!current_process && !ready_queue.empty()) {
            current_process = ready_queue.front();
            ready_queue.pop();
            current_process->set_state(ProcessState::RUNNING);
        }

        if (current_process) {
            bool finished = current_process->execute_burst(1);
            tick_count++;

            for (auto &p : all_processes)
                if (p.second != current_process && p.second->get_state() == ProcessState::READY)
                    p.second->add_waiting_time(1);

            current_process->add_turnaround_time(1);

            if (finished) {
                current_process->set_state(ProcessState::TERMINATED);
                current_process = nullptr;
            } else if (tick_count % quantum == 0) {
                current_process->set_state(ProcessState::READY);
                ready_queue.push(current_process);
                current_process = nullptr;
            }
        }
    }
}

std::string SchedulerRR::ps() const {
    std::ostringstream oss;
    for (auto &p : all_processes) {
        oss << "PID=" << p.first << " Name=" << p.second->get_name() << " State=";
        switch (p.second->get_state()) {
        case ProcessState::NEW: oss << "NEW"; break;
        case ProcessState::READY: oss << "READY"; break;
        case ProcessState::RUNNING: oss << "RUNNING"; break;
        case ProcessState::WAITING: oss << "WAITING"; break;
        case ProcessState::TERMINATED: oss << "TERMINATED"; break;
        }
        oss << "\n";
    }
    return oss.str();
}

std::map<int, std::pair<int, int>> SchedulerRR::collect_metrics() {
    std::map<int, std::pair<int, int>> metrics;
    for (auto &p : all_processes) {
        metrics[p.first] = {p.second->get_waiting_time(), p.second->get_turnaround_time()};
    }
    return metrics;
}
void SchedulerRR::tick() {
    run(1);
}

void SchedulerRR::kill_process(int pid) {
    auto it = all_processes.find(pid);
    if (it != all_processes.end()) {
        it->second->set_state(ProcessState::TERMINATED);
        std::cout << "Proceso PID=" << pid << " terminado." << std::endl;
        
        // Si es el proceso actual, liberarlo
        if (current_process && current_process->get_pid() == pid) {
            current_process = nullptr;
        }
    } else {
        std::cout << "Error: Proceso PID=" << pid << " no encontrado." << std::endl;
    }
}

void SchedulerRR::show_metrics() const {
    std::cout << "\n========================================" << std::endl;
    std::cout << "       METRICAS DEL SISTEMA" << std::endl;
    std::cout << "========================================" << std::endl;
    
    int completed = 0;
    int total_wait = 0;
    int total_turnaround = 0;
    
    std::cout << "\nDetalle de procesos:" << std::endl;
    std::cout << "PID  Name    Estado      Wait  Turnaround" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    for (const auto& p : all_processes) {
        std::cout << std::setw(3) << p.first << "  "
                  << std::setw(6) << std::left << p.second->get_name() << "  ";
        
        switch(p.second->get_state()) {
            case ProcessState::NEW: std::cout << "NEW       "; break;
            case ProcessState::READY: std::cout << "READY     "; break;
            case ProcessState::RUNNING: std::cout << "RUNNING   "; break;
            case ProcessState::WAITING: std::cout << "WAITING   "; break;
            case ProcessState::TERMINATED: std::cout << "TERMINATED"; break;
        }
        
        std::cout << "  " << std::setw(4) << p.second->get_waiting_time()
                  << "  " << std::setw(10) << p.second->get_turnaround_time()
                  << std::endl;
        
        if (p.second->get_state() == ProcessState::TERMINATED) {
            completed++;
            total_wait += p.second->get_waiting_time();
            total_turnaround += p.second->get_turnaround_time();
        }
    }
    
    std::cout << "\n----------------------------------------" << std::endl;
    std::cout << "Total de procesos: " << all_processes.size() << std::endl;
    std::cout << "Procesos completados: " << completed << std::endl;
    std::cout << "Quantum: " << quantum << std::endl;
    std::cout << "Ticks ejecutados: " << tick_count << std::endl;
    
    if (completed > 0) {
        double avg_wait = static_cast<double>(total_wait) / completed;
        double avg_turnaround = static_cast<double>(total_turnaround) / completed;
        
        std::cout << "\nTiempo de espera promedio: " << std::fixed 
                  << std::setprecision(2) << avg_wait << std::endl;
        std::cout << "Tiempo de retorno promedio: " << avg_turnaround << std::endl;
        
        // Fairness (desviación estándar)
        double sum_squares = 0;
        for (const auto& p : all_processes) {
            if (p.second->get_state() == ProcessState::TERMINATED) {
                double diff = p.second->get_waiting_time() - avg_wait;
                sum_squares += diff * diff;
            }
        }
        double std_dev = sqrt(sum_squares / completed);
        std::cout << "Fairness (desv. estandar): " << std_dev << std::endl;
    }
    
    std::cout << "========================================\n" << std::endl;
}