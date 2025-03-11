/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:43:29 by luinasci          #+#    #+#             */
/*   Updated: 2025/03/11 18:17:33 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_program(t_program *prog, t_philo *philos,
				pthread_mutex_t *forks, t_config *cfg)
{
	t_philo_init	init_data;
	int				i;

	i = 0;
	prog->dead_flag = 0;
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->write_lock, NULL);
	prog->philos = philos;
	prog->start_time = get_current_time();
	init_forks(forks, cfg->num_philos);
	init_data.prog = prog;
	init_data.forks = forks;
	init_data.cfg = cfg;
	while (i < cfg->num_philos)
	{
		init_data.id = i;
		init_philosopher(&philos[i], &init_data);
		i++;
	}
}

void	init_forks(pthread_mutex_t *forks, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

int	init_resources(t_philo **philos, pthread_mutex_t **forks, int count)
{
	*philos = malloc(sizeof(t_philo) * count);
	*forks = malloc(sizeof(pthread_mutex_t) * count);
	if (!*philos || !*forks)
	{
		free(*philos);
		free(*forks);
		return (0);
	}
	return (1);
}

void	set_philo_forks(t_philo *philo, t_philo_init *init)
{
	philo->r_fork = &init->forks[init->id];
	philo->l_fork = &init->forks[(init->id + 1) % init->cfg->num_philos];
}

void	init_philosopher(t_philo *philo, t_philo_init *init)
{
	philo->id = init->id;
	philo->meals_eaten = 0;
	philo->last_meal = init->prog->start_time;
	philo->time_to_die = init->cfg->time_to_die;
	philo->time_to_eat = init->cfg->time_to_eat;
	philo->time_to_sleep = init->cfg->time_to_sleep;
	philo->start_time = init->prog->start_time;
	philo->num_of_philos = init->cfg->num_philos;
	philo->num_times_to_eat = init->cfg->meal_goal;
	philo->dead = &init->prog->dead_flag;
	set_philo_forks(philo, init);
	philo->write_lock = &init->prog->write_lock;
	philo->dead_lock = &init->prog->dead_lock;
	pthread_mutex_init(&philo->meal_lock, NULL);
}
