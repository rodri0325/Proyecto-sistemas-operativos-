#include "cli.h"
#include <iostream>
#include <sstream>
#include <vector>

CLI::CLI(int quantum, int frames) 
    : scheduler(quantum), 
      memory_lru(frames),
      memory_fifo(frames),
      running(true),
      use_fifo(false) {}

void CLI::show_banner() {
    std::cout << "\n╔═══════════════════════════════════════════╗" << std::endl;
    std::cout << "║   SIMULADOR DE SISTEMA OPERATIVO v1.0    ║" << std::endl;
    std::cout << "║                                           ║" << std::endl;
    std::cout << "║  Planificacion: Round Robin (Q=2)        ║" << std::endl;
    std::cout << "║  Memoria: LRU + FIFO (3 marcos)          ║" << std::endl;
    std::cout << "║                                           ║" << std::endl;
    std::cout << "║  Escriba 'help' para ver comandos        ║" << std::endl;
    std::cout << "╚═══════════════════════════════════════════╝" << std::endl;
}

void CLI::show_help() {
    std::cout << "\n=== COMANDOS DISPONIBLES ===" << std::endl;
    std::cout << "\nPLANIFICACION CPU:" << std::endl;
    std::cout << "  new <burst>      - Crear proceso con tiempo de rafaga" << std::endl;
    std::cout << "  ps               - Listar todos los procesos" << std::endl;
    std::cout << "  tick             - Avanzar 1 unidad de tiempo" << std::endl;
    std::cout << "  run <n>          - Ejecutar n ticks" << std::endl;
    std::cout << "  kill <pid>       - Terminar proceso por PID" << std::endl;
    std::cout << "  metrics          - Ver metricas del sistema" << std::endl;
    
    std::cout << "\nGESTION DE MEMORIA:" << std::endl;
    std::cout << "  access <page>    - Acceder a una pagina" << std::endl;
    std::cout << "  memstats         - Mostrar estadisticas de memoria" << std::endl;
    std::cout << "  switch <lru|fifo>- Cambiar algoritmo de memoria" << std::endl;
    std::cout << "  simulate <seq>   - Simular secuencia (ej: 1,2,3,4)" << std::endl;
    
    std::cout << "\nOTROS:" << std::endl;
    std::cout << "  help             - Mostrar esta ayuda" << std::endl;
    std::cout << "  exit             - Salir del simulador\n" << std::endl;
}

void CLI::cmd_new(const std::string& args) {
    std::istringstream iss(args);
    int burst;
    
    if (!(iss >> burst) || burst <= 0) {
        std::cout << "Error: Uso correcto -> new <burst_time>" << std::endl;
        std::cout << "Ejemplo: new 5" << std::endl;
        return;
    }
    
    std::vector<int> bursts = {burst};
    static int proc_num = 1;
    auto process = scheduler.new_process("P" + std::to_string(proc_num++), bursts);
    std::cout << "Proceso creado: PID=" << process->get_pid() 
              << " Name=" << process->get_name() 
              << " Burst=" << burst << std::endl;
}

void CLI::cmd_ps() {
    std::cout << "\n=== LISTA DE PROCESOS ===" << std::endl;
    std::cout << scheduler.ps();
}

void CLI::cmd_tick() {
    std::cout << "\n--- Ejecutando 1 tick ---" << std::endl;
    scheduler.tick();
}

void CLI::cmd_run(const std::string& args) {
    std::istringstream iss(args);
    int n;
    
    if (!(iss >> n) || n <= 0) {
        std::cout << "Error: Uso correcto -> run <n>" << std::endl;
        std::cout << "Ejemplo: run 10" << std::endl;
        return;
    }
    
    std::cout << "\n>>> Ejecutando " << n << " ticks <<<" << std::endl;
    scheduler.run(n);
}

void CLI::cmd_kill(const std::string& args) {
    std::istringstream iss(args);
    int pid;
    
    if (!(iss >> pid)) {
        std::cout << "Error: Uso correcto -> kill <pid>" << std::endl;
        std::cout << "Ejemplo: kill 1" << std::endl;
        return;
    }
    
    scheduler.kill_process(pid);
}

void CLI::cmd_metrics() {
    scheduler.show_metrics();
}

void CLI::cmd_access(const std::string& args) {
    std::istringstream iss(args);
    int page;
    
    if (!(iss >> page) || page < 0) {
        std::cout << "Error: Uso correcto -> access <page>" << std::endl;
        std::cout << "Ejemplo: access 3" << std::endl;
        return;
    }
    
    std::cout << "\nUsando algoritmo " << (use_fifo ? "FIFO" : "LRU") << ":" << std::endl;
    if (use_fifo) {
        memory_fifo.access_page(page);
    } else {
        memory_lru.access_page(page);
    }
}

void CLI::cmd_memstats() {
    if (use_fifo) {
        memory_fifo.show_stats();
    } else {
        memory_lru.show_stats();
    }
}

void CLI::cmd_switch(const std::string& args) {
    std::istringstream iss(args);
    std::string algo;
    iss >> algo;
    
    if (algo == "fifo") {
        use_fifo = true;
        std::cout << "Algoritmo cambiado a FIFO" << std::endl;
    } else if (algo == "lru") {
        use_fifo = false;
        std::cout << "Algoritmo cambiado a LRU" << std::endl;
    } else {
        std::cout << "Error: Uso correcto -> switch <lru|fifo>" << std::endl;
    }
}

void CLI::cmd_simulate(const std::string& args) {
    std::istringstream iss(args);
    std::string seq_str;
    iss >> seq_str;
    
    if (seq_str.empty()) {
        std::cout << "Error: Uso correcto -> simulate <secuencia>" << std::endl;
        std::cout << "Ejemplo: simulate 1,2,3,4,1,2,5" << std::endl;
        return;
    }
    
    std::vector<int> sequence;
    std::stringstream ss(seq_str);
    std::string item;
    
    while (std::getline(ss, item, ',')) {
        try {
            sequence.push_back(std::stoi(item));
        } catch (...) {
            std::cout << "Error: Secuencia invalida" << std::endl;
            return;
        }
    }
    
    std::cout << "\nSimulando secuencia con " << (use_fifo ? "FIFO" : "LRU") << ":" << std::endl;
    std::cout << "Secuencia: ";
    for (int p : sequence) std::cout << p << " ";
    std::cout << "\n" << std::endl;
    
    for (int page : sequence) {
        if (use_fifo) {
            memory_fifo.access_page(page);
        } else {
            memory_lru.access_page(page);
        }
    }
    
    std::cout << "\n--- Simulacion completada ---" << std::endl;
    if (use_fifo) {
        memory_fifo.show_stats();
    } else {
        memory_lru.show_stats();
    }
}

void CLI::start() {
    show_banner();
    
    std::string line;
    while (running) {
        std::cout << "\nOS> ";
        std::getline(std::cin, line);
        
        if (line.empty()) continue;
        
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;
        
        std::string args;
        std::getline(iss, args);
        
        size_t start = args.find_first_not_of(" \t");
        if (start != std::string::npos) {
            args = args.substr(start);
        }
        
        if (cmd == "new") cmd_new(args);
        else if (cmd == "ps") cmd_ps();
        else if (cmd == "tick") cmd_tick();
        else if (cmd == "run") cmd_run(args);
        else if (cmd == "kill") cmd_kill(args);
        else if (cmd == "metrics") cmd_metrics();
        else if (cmd == "access") cmd_access(args);
        else if (cmd == "memstats") cmd_memstats();
        else if (cmd == "switch") cmd_switch(args);
        else if (cmd == "simulate") cmd_simulate(args);
        else if (cmd == "help") show_help();
        else if (cmd == "exit" || cmd == "quit") {
            std::cout << "\nGracias por usar el simulador. Adios!\n" << std::endl;
            running = false;
        }
        else {
            std::cout << "Comando desconocido: '" << cmd << "'" << std::endl;
            std::cout << "Escriba 'help' para ver los comandos disponibles." << std::endl;
        }
    }
}