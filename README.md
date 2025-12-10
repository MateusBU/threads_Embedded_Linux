# Embedded Linux GPIO Control with Threads

This project demonstrates how to build a simple **embedded Linux application** using:

- POSIX **threads (pthreads)** for multitasking  
- **libgpiod** for GPIO access  
- A modular architecture (`app`, `input`, `output`, `bsp`)  
- Periodic execution of tasks (software "tasks" similar to an RTOS)

The application reads a button and changes the behavior of an LED according to a counter that cycles through multiple modes.

---

### Threads Used

| Thread       | Period | Function |
|--------------|--------|----------|
| `app_task()` | 100 ms | Updates application logic |
| `gpio_task()` | 1 ms  | Reads GPIO inputs and updates outputs |

---

## 🔘 LED Behavior Logic

Pressing the button increments a counter (`counter`), cycling through **4 modes**:

| Counter | LED Behavior |
|---------|--------------|
| **0** | LED OFF |
| **1** | LED ON |
| **2** | LED blinks (toggle every cycle) |
| **3** | LED blinks with custom timing (15 ON / 8 OFF loop) |

When the value exceeds 3, it resets to 0.

---

## 📌 Main Application (main.c)

Two threads are created:

```c
pthread_create(&th1, NULL, app_task, NULL);
pthread_create(&th2, NULL, gpio_task, NULL);


