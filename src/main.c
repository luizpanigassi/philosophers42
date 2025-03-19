/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:02 by luinasci          #+#    #+#             */
/*   Updated: 2025/03/11 17:08:35 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_philosopher_errors(t_program *prog, t_philo *philos,
									pthread_mutex_t *forks)
{
	cleanup_resources(prog, philos, forks);
	return (1);
}

void	parse_arguments(t_config *cfg, int argc, char **argv)
{
	cfg->num_philos = atoi(argv[1]);
	cfg->time_to_die = atoi(argv[2]);
	cfg->time_to_eat = atoi(argv[3]);
	cfg->time_to_sleep = atoi(argv[4]);
	cfg->meal_goal = -1;
	if (argc == 6)
		cfg->meal_goal = atoi(argv[5]);
}

int	create_monitor(t_program *prog, pthread_t *monitor)
{
	if (pthread_create(monitor, NULL, monitor_routine, prog))
	{
		printf("Error: Monitor creation failed\n");
		pthread_mutex_lock(&prog->dead_lock);
		prog->dead_flag = 1;
		pthread_mutex_unlock(&prog->dead_lock);
		return (0);
	}
	return (1);
}

int	create_philosophers(t_philo *philos, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pthread_create(&philos[i].thread, NULL, philo_routine, &philos[i]))
		{
			printf("Error: Failed to create philosopher %d\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_config		cfg;
	t_program		prog;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		monitor;

	if (check_arg_count(argc, argv) || !is_valid_input(argc, argv))
		return (1);
	if (argc < 5 || argc > 6 || !is_valid_input(argc, argv))
		return (1);
	parse_arguments(&cfg, argc, argv);
	if (!init_resources(&philos, &forks, cfg.num_philos))
		return (1);
	init_program(&prog, philos, forks, &cfg);
	if (!create_philosophers(philos, cfg.num_philos))
	{
		pthread_mutex_lock(&prog.dead_lock);
		prog.dead_flag = 1;
		pthread_mutex_unlock(&prog.dead_lock);
		return (handle_philosopher_errors(&prog, philos, forks));
	}
	create_monitor(&prog, &monitor);
	join_threads(&prog, monitor, cfg.num_philos);
	cleanup_resources(&prog, philos, forks);
	return (0);
}
