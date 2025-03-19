/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:44:08 by luinasci          #+#    #+#             */
/*   Updated: 2025/03/10 19:36:23 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_program *program,
		pthread_mutex_t *forks, int num_philos)
{
	int	i;

	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&program->philos[i].meal_lock);
		i++;
	}
	pthread_mutex_destroy(&program->dead_lock);
	pthread_mutex_destroy(&program->write_lock);
}

void	cleanup_resources(t_program *prog,
				t_philo *philos, pthread_mutex_t *forks)
{
	destroy_mutexes(prog, forks, prog->philos[0].num_of_philos);
	free(philos);
	free(forks);
}
