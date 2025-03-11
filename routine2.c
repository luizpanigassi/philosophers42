/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 19:37:01 by luinasci          #+#    #+#             */
/*   Updated: 2025/03/11 17:10:39 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	think_action(t_philo *philo)
{
	if (check_simulation_end(philo))
		return ;
	log_action(philo, "is thinking", "\033[36m");
}

void	eat_action(t_philo *philo)
{
	pick_forks(philo);
	if (check_simulation_end(philo))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	update_meal_stats(philo);
	log_action(philo, "is eating", "\033[32m");
	if (perform_action_delay(philo, philo->time_to_eat))
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	sleep_action(t_philo *philo)
{
	if (check_simulation_end(philo))
		return ;
	log_action(philo, "is sleeping", "\033[35m");
	perform_action_delay(philo, philo->time_to_sleep);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_current_time() < philo->start_time)
		usleep(100);
	while (!check_simulation_end(philo))
	{
		think_action(philo);
		eat_action(philo);
		sleep_action(philo);
	}
	return (NULL);
}
