/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:51 by luinasci          #+#    #+#             */
/*   Updated: 2025/03/11 18:37:16 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death_flag(t_program *p)
{
	int	flag;

	pthread_mutex_lock(&p->dead_lock);
	flag = p->dead_flag;
	pthread_mutex_unlock(&p->dead_lock);
	return (flag);
}

int	check_philosopher_death(t_program *p, int i)
{
	size_t	time_since_meal;
	size_t	timestamp;
	size_t	current_time;
	int		died;

	current_time = get_current_time();
	pthread_mutex_lock(&p->philos[i].meal_lock);
	time_since_meal = current_time - p->philos[i].last_meal;
	died = (time_since_meal > p->philos[i].time_to_die);
	pthread_mutex_unlock(&p->philos[i].meal_lock);
	if (!died)
		return (0);
	pthread_mutex_lock(p->philos[i].write_lock);
	timestamp = get_current_time() - p->start_time;
	print_formatted_time(timestamp);
	printf("Philosopher \033[34m%d\033[0m \033[31mdied\033[0m\n", p->philos[i].id);
	pthread_mutex_unlock(p->philos[i].write_lock);
	pthread_mutex_lock(&p->dead_lock);
	p->dead_flag = 1;
	pthread_mutex_unlock(&p->dead_lock);
	return (1);
}

int	check_all_deaths(t_program *p)
{
	int	i;

	i = p->philos[0].num_of_philos - 1;
	while (i >= 0)
	{
		if (check_philosopher_death(p, i))
			return (1);
		i--;
	}
	return (0);
}

int	check_meals_completion(t_program *p)
{
	int	i;
	int	n;
	int	all_ate;

	i = 0;
	n = p->philos[0].num_of_philos;
	all_ate = 1;
	while (i < n)
	{
		pthread_mutex_lock(&p->philos[i].meal_lock);
		if (p->philos[i].meals_eaten < p->philos[i].num_times_to_eat)
			all_ate = 0;
		pthread_mutex_unlock(&p->philos[i].meal_lock);
		i++;
	}
	return (all_ate);
}

void	*monitor_routine(void *arg)
{
	t_program	*p;
	size_t		start;

	p = (t_program *)arg;
	start = p->start_time;
	while (get_current_time() < start)
		usleep(100);
	while (1)
	{
		if (check_death_flag(p) || check_all_deaths(p))
			break ;
		if (p->philos[0].num_times_to_eat != -1 && check_meals_completion(p))
		{
			pthread_mutex_lock(&p->dead_lock);
			p->dead_flag = 1;
			pthread_mutex_unlock(&p->dead_lock);
			pthread_mutex_lock(p->philos[0].write_lock);
			printf("\033[32mAll philosophers ate enough!\033[0m\n");
			pthread_mutex_unlock(p->philos[0].write_lock);
			break ;
		}
	}
	return (NULL);
}
