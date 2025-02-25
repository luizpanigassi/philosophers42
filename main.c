/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:02 by luinasci          #+#    #+#             */
/*   Updated: 2025/02/18 18:36:26 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	if (!is_valid_input(argc, argv))
	{
		return 1;
	}

	int num_philos = atoi(argv[1]);
	t_program program;
	t_philo philos[num_philos];
	pthread_mutex_t forks[num_philos];

	// Initialize program and philosophers
	init_program(&program, philos, forks, num_philos, argc, argv);

	// Create philosopher threads
	int i = 0;
	while (i < num_philos)
	{
		pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]);
		i++;
	}

	// Create monitor thread
	pthread_t monitor;
	if (pthread_create(&monitor, NULL, monitor_routine, &program) != 0)
	{
		printf("Error: Failed to create monitor thread\n");
		return 1;
	}
	printf("Monitor thread created successfully.\n");
	// Join philosopher threads
	i = 0;
	while (i < num_philos)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}

	// Join monitor thread
	pthread_join(monitor, NULL);

	// Clean up mutexes
	destroy_mutexes(&program, forks, num_philos);

	return 0;
}
