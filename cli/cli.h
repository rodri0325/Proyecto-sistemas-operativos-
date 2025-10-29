#ifndef CLI_H
#define CLI_H

#include "../modules/cpu/scheduler_rr.h"
#include "../modules/mem/mem_manager.h"
#include "../modules/mem/fifo_manager.h"
#include <string>

class CLI {
private:
    SchedulerRR scheduler;
    MemManager memory_lru;
    FIFOManager memory_fifo;
    bool running;
    bool use_fifo;
    
    void show_banner();
    void show_help();
    
    void cmd_new(const std::string& args);
    void cmd_ps();
    void cmd_tick();
    void cmd_run(const std::string& args);
    void cmd_kill(const std::string& args);
    void cmd_metrics();
    
    void cmd_access(const std::string& args);
    void cmd_memstats();
    void cmd_switch(const std::string& args);
    void cmd_simulate(const std::string& args);

public:
    CLI(int quantum = 2, int frames = 3);
    void start();
};

#endif