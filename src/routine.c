/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:41 by luinasci          #+#    #+#             */
/*   Updated: 2025/03/11 17:19:26 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_simulation_end(t_philo *philo)
{
	int	end;

	pthread_mutex_lock(philo->dead_lock);
	end = *philo->dead;
	pthread_mutex_unlock(philo->dead_lock);
	return (end);
}

void	log_action(t_philo *philo, char *msg, char *color)
{
	size_t	current_time;

	pthread_mutex_lock(philo->write_lock);
	current_time = get_current_time() - philo->start_time;
	print_formatted_time(current_time);
	printf("Philosopher \033[34m%d\033[0m %s%s\033[0m\n", philo->id, color, msg);
	pthread_mutex_unlock(philo->write_lock);
}

void	pick_forks(t_philo *philo)
{
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
	if (!check_simulation_end(philo))
		log_action(philo, "has taken forks", "\033[33m");
}

void	update_meal_stats(t_philo *philo)
{
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_lock);
}

int	perform_action_delay(t_philo *philo, size_t delay)
{
	size_t	start;

	start = get_current_time();
	while (get_current_time() - start < delay)
	{
		if (check_simulation_end(philo))
			return (1);
		usleep(100);
	}
	return (0);
}
