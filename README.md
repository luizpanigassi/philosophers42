# philo_deliver

A solution for the Philosopher's Dinner problem!

## Overview

Alright, here's the story. Around a round table, we have 5 philosophers. Each of them has a plate of food in front of them. Each of them has one fork to its right (which in a circular table, means that every philosopher has one fork on each side of his/her plate).

The philosophers are either thinking, sleeping, or eating. They will carry out these actions individually, and they will never do more than one action at a time. The philosophers may starve, so it's important to stop thinking/sleeping and start eating. BUT - there is always a but - to eat, the philosopher needs both forks. Seems easy right? But think about it. When a philosopher starts eating, he takes both forks. So, this means that the philosopher right beside him has one less fork to eat, so, he simply cannot eat (who the hell uses two forks to eat?). And this is where we come in. How can we manage the forks and the philosophers so that they eat, think and sleep without dying?

This is a direct parallel to processes and threads. Threads are parts of the process which run at the same time. But that's the problem, eventually a thread may take up all the forks, and the other threads can die, which means your program will crash. And that's where multithread computing comes in.

Mutexes and threads. This is the main topic here. The philosophers are threads, parts of a larger process, the dinner. The forks are mutexes, functions that will regulate the consumption of resources.

In my solution, I've developed a "waiter". A monitor of sorts, used to control who is eating, who is dying, and who gets the forks in order, so that everyone can eat, pray and love, and survive.

## How it works

- Each philosopher is represented by a thread.
- Forks are represented by mutexes to prevent race conditions.
- Philosophers must acquire both forks (mutexes) before eating.
- A monitor thread ("waiter") checks for philosopher deaths and meal completion.
- The simulation ends if a philosopher dies or all have eaten the required number of meals.

## Usage

1. **Clone the repository**  
   ```
   git clone <repo-url>
   cd philo_deliver
   ```

2. **Build the project**  
   ```
   make
   ```

3. **Run the simulation**  
   ```
   ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_meals (optional)]
   ```
   - `number_of_philosophers`: Number of philosophers (and forks)
   - `time_to_die`: Time (ms) a philosopher can go without eating before dying
   - `time_to_eat`: Time (ms) a philosopher spends eating
   - `time_to_sleep`: Time (ms) a philosopher spends sleeping
   - `number_of_meals`: (Optional) Number of times each philosopher must eat before simulation ends

   Example:
   ```
   ./philo 5 800 200 200 3
   ```

## Project Structure

- [`includes/philo.h`](philo_deliver/includes/philo.h): Header file with structures and function prototypes.
- [`src/`](philo_deliver/src/): Source files implementing the logic:
  - `main.c`: Entry point and setup
  - `init.c`: Initialization routines
  - `routine.c`, `routine2.c`: Philosopher actions and routines
  - `monitor.c`: Monitor ("waiter") logic
  - `cleanup.c`: Resource cleanup
- [`utils/utils.c`](philo_deliver/utils/utils.c): Utility functions.

## Concepts Demonstrated

- Multithreading with pthreads
- Mutexes for resource management
- Thread synchronization and monitoring
- Deadlock avoidance and starvation prevention

## License

This project is for educational purposes.

---

If you want to run a simulation, simply copy the repository, run my makefile (simply run `make`), and then...

```
./philo [number of philosophers] [time to die] [time to eat] [time to sleep] [number of meals to eat (optional)]
```

And watch the magic happen.
