<b>A solution for the Philosopher's Dinner problem!</b>

Alright, here's the story. Around a round table, we have 5 philosophers. Each of them
has a plate of food in front of them. Each of them has one fork to its right (which in a
circular table, means that every philosopher has one fork on each side of his/her plate).

The philosophers are either thinking, sleeping, or eating. They will carry out these actions
individually, and they will never do more than one action at a time. The philosophers may starve,
so it's important to stop thinking/sleeping and start eating. BUT - there is always a but - to eat,
the philosopher needs both forks. Seems easy right? But think about it. When a philospher starts
eating, he takes both forks. So, this means that the philosopher right beside him has one less fork
to eat, so, he simply cannot eat (who the hell uses two forks to eat?). And this is where we come in.
How can we manage the forks and the philosophers so that they eat, think and sleep without dying?

This is a direct parallel to processes and threads. Threads are parts of the process which run at
the same time. But that's the problem, eventually a thread may take up all the forks, and the other
threads can die, which means your program will crash. And that's where multithread computing comes in.

Mutexes and threads. This is the main topic here. The philosophers are threads, parts of a larger
process, the dinner. The forks are mutexes, functions that will regulate the consumption of resources.

In my solution, I've developed a "waiter". A monitor of sorts, used to control who is eating, who is
dying, and who gets the forks in order, so that everyone can eat, pray and love, and survive.

If you want to run a simulation, simply copy the repository, run my makefile (simply run make), and then...

./philo [number of philosophers] [time to die] [time to eat] [number of meals to eat (optional)]

And watch the magic happen.
