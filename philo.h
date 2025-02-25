/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 15:41:51 by luinasci          #+#    #+#             */
/*   Updated: 2025/02/19 17:12:53 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <limits.h>

// Philosopher states
#define THINKING 2
#define HUNGRY 1
#define EATING 0

// Philosopher structure
typedef struct s_philo
{
    pthread_t thread;
    int id;
    int state;
    int meals_eaten;
    size_t last_meal;
    size_t time_to_die;
    size_t time_to_eat;
    size_t time_to_sleep;
    size_t start_time;
    int num_of_philos;
    int num_times_to_eat;
    int *dead;
    pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
    pthread_mutex_t *write_lock;
    pthread_mutex_t *dead_lock;
    pthread_mutex_t *meal_lock;
} t_philo;

// Program structure
typedef struct s_program
{
    int dead_flag;
    pthread_mutex_t dead_lock;
    pthread_mutex_t meal_lock;
    pthread_mutex_t write_lock;
    pthread_mutex_t fork_manager;
    t_philo *philos;
} t_program;

// Function prototypes
int is_valid_input(int argc, char **argv);
void init_program(t_program *program, t_philo *philos, pthread_mutex_t *forks, int num_philos, int argc, char **argv);
void *philo_routine(void *arg);
void *monitor_routine(void *arg);
void destroy_mutexes(t_program *program, pthread_mutex_t *forks, int num_philos);
size_t get_current_time(void);
void print_formatted_time();

#endif
