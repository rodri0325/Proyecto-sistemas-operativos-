# Proyecto-sistemas-operativos-
Proyecto final Sistemas Operativos. Incluye estructura de carpetas, backlog, borrador del informe técnico y plan de pruebas según los lineamientos del curso.

#  Simulador de Sistema Operativo

**Proyecto Final - Sistemas Operativos 2025**

##  Descripción

Simulador educativo de un Sistema Operativo que implementa:

- ✅ **Planificación de CPU**: Round Robin con quantum configurable
- ✅ **Gestión de Memoria**: Algoritmos FIFO y LRU
- ✅ **Sincronización**: Problema Productor-Consumidor con Mutex
- ✅ **Métricas**: Tiempos de espera, retorno, fairness, PFF

##  Estructura del Proyecto
```
ProyectofinalSO/
├── cli/                    # Interfaz de línea de comandos
├── modules/
│   ├── cpu/               # Planificador y PCB
│   ├── mem/               # Gestión de memoria (FIFO, LRU)
│   └── sync/              # Sincronización (Mutex)
├── docs/                  # Documentación
├── tests/                 # Pruebas
└── main.cpp              # Punto de entrada
```

##  Compilación
```bash
g++ -std=c++17 -static -o os_simulator.exe main.cpp modules/cpu/pcb.cpp modules/cpu/scheduler_rr.cpp modules/mem/mem_manager.cpp modules/mem/fifo_manager.cpp
```

##  Ejecución
```bash
.\os_simulator.exe
```

## 📊 Características Implementadas

### 1. Planificador Round Robin
- Quantum configurable
- Cola de procesos listos
- Cambio de contexto automático

### 2. Gestión de Memoria
- **FIFO**: First In First Out
- **LRU**: Least Recently Used
- Visualización de marcos
- Cálculo de PFF (Page Fault Frequency)

### 3. Métricas de Rendimiento
- Tiempo de espera promedio
- Tiempo de retorno (turnaround)
- Fairness (desviación estándar)

### 4. Sincronización
- Implementación con `std::mutex`
- Problema Productor-Consumidor

##  Autor

[Tu Nombre]

##  Licencia

Proyecto académico - Universidad [Nombre]
