/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:41 by luinasci          #+#    #+#             */
/*   Updated: 2025/02/19 17:29:03 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	while (1)
	{
		pthread_mutex_lock(philo->dead_lock);
		if (*philo->dead) // Check for termination condition
		{
			pthread_mutex_unlock(philo->dead_lock);
			break;
		}
		pthread_mutex_unlock(philo->dead_lock);

		// Thinking
		pthread_mutex_lock(philo->write_lock);
		print_formatted_time();
		printf("Philosopher \033[34m%d\033[0m \033[37m \033[0m \033[36mis thinking\033[0m\n", philo->id);
		pthread_mutex_unlock(philo->write_lock);

		// Implement fork pickup order to prevent deadlock
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			pthread_mutex_lock(philo->r_fork);
		}
		else
		{
			pthread_mutex_lock(philo->r_fork);
			pthread_mutex_lock(philo->l_fork);
		}

		pthread_mutex_lock(philo->write_lock);
		print_formatted_time();
		printf("Philosopher \033[34m%d\033[0m \033[37m \033[0m \033[33mhas taken forks\033[0m\n", philo->id);
		pthread_mutex_unlock(philo->write_lock);

		// Eating
		pthread_mutex_lock(philo->meal_lock);
		philo->last_meal = get_current_time();
		philo->state = EATING;
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->meal_lock);

		pthread_mutex_lock(philo->write_lock);
		print_formatted_time();
		printf("Philosopher \033[34m%d\033[0m \033[37m \033[0m \033[32mis eating\033[0m\n", philo->id);
		pthread_mutex_unlock(philo->write_lock);

		usleep(philo->time_to_eat * 1000);

		// Release forks
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);

		// Sleeping
		pthread_mutex_lock(philo->write_lock);
		print_formatted_time();
		printf("Philosopher \033[34m%d\033[0m \033[37m \033[0m \033[35mis sleeping\033[0m\n", philo->id);
		pthread_mutex_unlock(philo->write_lock);

		usleep(philo->time_to_sleep * 1000);
	}

	return NULL;
}
