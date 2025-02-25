/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:29 by luinasci          #+#    #+#             */
/*   Updated: 2025/02/19 16:23:14 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_program(t_program *program, t_philo *philos, pthread_mutex_t *forks, int num_philos, int argc, char **argv)
{
	// Initialize program variables
	program->dead_flag = 0;
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->fork_manager, NULL);

	// Initialize forks (mutexes)
	int i = 0;
	while (i < num_philos)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}

	// Initialize philosophers
	program->philos = philos; // Ensure philos is assigned to program->philos
	i = 0;
	while (i < num_philos)
	{
		philos[i].id = i + 1;
		philos[i].state = THINKING;
		philos[i].meals_eaten = 0;
		philos[i].last_meal = get_current_time();
		philos[i].time_to_die = (size_t)atoi(argv[2]);
		philos[i].time_to_eat = (size_t)atoi(argv[3]);
		philos[i].time_to_sleep = (size_t)atoi(argv[4]);
		philos[i].start_time = get_current_time();
		philos[i].num_of_philos = num_philos;
		philos[i].num_times_to_eat = (argc == 6) ? atoi(argv[5]) : -1;
		philos[i].dead = &program->dead_flag;
		philos[i].r_fork = &forks[i];
		philos[i].l_fork = &forks[(i + 1) % num_philos];
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		i++;
	}
}
