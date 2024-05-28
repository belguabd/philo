/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:42:33 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/28 15:21:38 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <limits.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <sys/time.h>

typedef struct monitor t_mtr;

typedef struct philo
{
	pthread_t th;
	int id;
	long start;
	size_t time_die;
	int time_eat;
	int time_sleep;
	size_t last_meal;
	int num_eat;
	pthread_mutex_t meal_mutex;
	t_mtr *mtr;

} t_philo;
typedef struct monitor
{
	t_philo **philo;
	pthread_mutex_t *forks;
	pthread_t thread_monitor;
	int stop_simulation;
	int num_philo;
	int stop_eat;
	int nbr_each_philo;
	int philo_ready;
	pthread_mutex_t print_mutex;
	pthread_mutex_t stop_simu_mutex;
	pthread_mutex_t check_is_died;
	pthread_mutex_t stop_eat_mutex;
	pthread_mutex_t num_eat_mutex;
	pthread_mutex_t wait_philos;

} t_mtr;

int ft_atoi(const char *str);
void ft_putendl_fd(char *s, int fd);
size_t ft_strlen(const char *s);
long ft_atoi_parsing(char *str);

#endif