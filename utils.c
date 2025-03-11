/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:44:00 by luinasci          #+#    #+#             */
/*   Updated: 2025/03/11 18:37:14 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid_input(int argc, char **argv)
{
	int		i;
	char	*endptr;
	long	val;

	if (argc < 5 || argc > 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (0);
	}
	i = 1;
	while (i < argc)
	{
		val = strtol(argv[i], &endptr, 10);
		if (*endptr != '\0' || val <= 0 || val > INT_MAX)
		{
			printf("Error: Invalid argument %s\n", argv[i]);
			return (0);
		}
		i++;
	}
	return (1);
}

size_t	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_formatted_time(size_t timestamp_ms)
{
	printf("[%zu] ", timestamp_ms);
}

void	join_threads(t_program *prog, pthread_t monitor, int count)
{
	int	i;

	i = 0;
	while (i < count)
		pthread_join(prog->philos[i++].thread, NULL);
	pthread_join(monitor, NULL);
}

int	check_arg_count(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_meals]\n", argv[0]);
		return (1);
	}
	return (0);
}
