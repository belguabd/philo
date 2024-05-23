/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:42:33 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/23 15:36:11 by belguabd         ###   ########.fr       */
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
#include <time.h>
#include <sys/time.h>

typedef struct monitor t_mtr;

typedef struct philo
{
	pthread_t th;
	int id;
	long start;
	int num_philo;
	int time_die;
	int time_eat;
	int time_sleep;
	int nbr_each_philo;
	t_mtr *mtr;

} t_philo;

typedef struct monitor
{
	t_philo **philo;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;

} t_mtr;

int ft_atoi(const char *str);
void ft_putendl_fd(char *s, int fd);
size_t ft_strlen(const char *s);

#endif