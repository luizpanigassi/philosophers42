/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:09:21 by luinasci          #+#    #+#             */
/*   Updated: 2025/03/11 18:37:15 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>

# define THINKING 2
# define HUNGRY 1
# define EATING 0

typedef struct s_philo
{
	pthread_t		thread;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	meal_lock;
	int				num_of_philos;
	int				num_times_to_eat;
	int				*dead;
	int				id;
	int				meals_eaten;
}	t_philo;

typedef struct s_program
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
	size_t			start_time;
}	t_program;

typedef struct s_config {
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	int		meal_goal;
	int		num_philos;
}	t_config;

typedef struct s_philo_init {
	t_program		*prog;
	pthread_mutex_t	*forks;
	t_config		*cfg;
	int				id;
}	t_philo_init;

size_t	get_current_time(void);
void	destroy_mutexes(t_program *program,
			pthread_mutex_t *forks, int num_philos);
void	cleanup_resources(t_program *prog,
			t_philo *philos, pthread_mutex_t *forks);
void	init_program(t_program *prog, t_philo *philos,
			pthread_mutex_t *forks, t_config *cfg);
void	init_forks(pthread_mutex_t *forks, int count);
void	init_philosopher(t_philo *philo, t_philo_init *init);
void	set_philo_forks(t_philo *philo, t_philo_init *init);
void	parse_arguments(t_config *cfg, int argc, char **argv);
void	*monitor_routine(void *arg);
void	log_action(t_philo *philo, char *msg, char *color);
void	pick_forks(t_philo *philo);
void	update_meal_stats(t_philo *philo);
void	think_action(t_philo *philo);
void	eat_action(t_philo *philo);
void	sleep_action(t_philo *philo);
void	*philo_routine(void *arg);
void	join_threads(t_program *prog, pthread_t monitor, int count);
void	print_formatted_time(size_t timestamp_ms);
int		create_philosophers(t_philo *philos, int count);
int		init_resources(t_philo **philos, pthread_mutex_t **forks, int count);
int		handle_philosopher_errors(t_program *prog, t_philo *philos,
			pthread_mutex_t *forks);
int		create_monitor(t_program *prog, pthread_t *monitor);
int		check_death_flag(t_program *p);
int		check_philosopher_death(t_program *p, int i);
int		check_all_deaths(t_program *p);
int		check_meals_completion(t_program *p);
int		is_valid_input(int argc, char **argv);
int		check_simulation_end(t_philo *philo);
int		perform_action_delay(t_philo *philo, size_t delay);
int		check_arg_count(int argc, char **argv);

#endif
