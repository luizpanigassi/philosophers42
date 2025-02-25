/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:51 by luinasci          #+#    #+#             */
/*   Updated: 2025/02/19 17:44:11 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
	t_program *program = (t_program *)arg;

	if (!program || !program->philos)
	{
		printf("Error: Invalid program or philosophers array\n");
		return NULL;
	}

	while (1)
	{
		usleep(1000); // Check every millisecond

		pthread_mutex_lock(&program->dead_lock);
		if (program->dead_flag)
		{
			pthread_mutex_unlock(&program->dead_lock);
			break;
		}
		pthread_mutex_unlock(&program->dead_lock);

		// Check if any philosopher has died
		int i = 0;
		while (i < program->philos[0].num_of_philos)
		{
			pthread_mutex_lock(&program->meal_lock);
			size_t time_since_last_meal = get_current_time() - program->philos[i].last_meal;
			if (time_since_last_meal > program->philos[i].time_to_die)
			{
				pthread_mutex_lock(&program->write_lock);
				print_formatted_time();
				printf("Philosopher \033[34m%d\033[0m \033[37m \033[0m \033[31mdied\033[0m\n", program->philos[i].id);
				pthread_mutex_unlock(&program->write_lock);
				pthread_mutex_lock(&program->dead_lock);
				program->dead_flag = 1;
				pthread_mutex_unlock(&program->dead_lock);
				pthread_mutex_unlock(&program->meal_lock);
				return NULL;
			}
			pthread_mutex_unlock(&program->meal_lock);
			i++;
		}
	}

	return NULL;
}
