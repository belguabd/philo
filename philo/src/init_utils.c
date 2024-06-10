/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:30:59 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/10 10:30:27 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	create_philos(t_mtr **mtr)
{
	int	i;

	i = 0;
	while (i < (*mtr)->num_philo)
	{
		if (pthread_create(&(*mtr)->philo[i]->th, NULL,
				&routine, (*mtr)->philo[i]))
			return (-1);
		i++;
	}
	if (pthread_create(&(*mtr)->thread_monitor, NULL,
			&monitor_philo, (*mtr)))
		return (-1);
	return (0);
}

t_philo	*init_philo(t_philo *philo, char *av[])
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (NULL);
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->time_die = ft_atoi_parsing(av[2]);
	philo->time_eat = ft_atoi_parsing(av[3]);
	philo->time_sleep = ft_atoi_parsing(av[4]);
	philo->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	philo->last_meal = philo->start;
	if (av[5])
		philo->num_eat = ft_atoi_parsing(av[5]);
	else
		philo->num_eat = -1;
	if (pthread_mutex_init(&philo->meal_mutex, NULL))
		return (NULL);
	return (philo);
}

int	init_monitor(t_mtr **mtr, char *av[])
{
	int	num_philo;

	(*mtr) = (t_mtr *)malloc(sizeof(t_mtr));
	if (!*mtr)
		return (-1);
	num_philo = ft_atoi_parsing(av[1]);
	(*mtr)->philo = (t_philo **)malloc(sizeof(t_philo *) * num_philo);
	if (!(*mtr)->philo)
		return (-1);
	(*mtr)->num_philo = num_philo;
	(*mtr)->forks = (pthread_mutex_t *)malloc
		(sizeof(pthread_mutex_t) * num_philo);
	if (!(*mtr)->forks)
		return (-1);
	(*mtr)->philo_ready = 0;
	return (0);
}

int	init_mutexes(t_mtr **mtr)
{
	int	i;

	i = 0;
	while (i < (*mtr)->num_philo)
		if (pthread_mutex_init(&(*mtr)->forks[i++], NULL))
			return (-1);
	if (pthread_mutex_init(&(*mtr)->print_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&(*mtr)->num_eat_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&(*mtr)->last_meal_mutex, NULL))
		return (-1);
	return (0);
}

int	init_philosophers(t_mtr **mtr, char *av[])
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < (*mtr)->num_philo)
	{
		philo = init_philo((*mtr)->philo[i], av);
		if (!philo)
			return (-1);
		(*mtr)->philo[i] = philo;
		(*mtr)->philo[i]->id = i + 1;
		(*mtr)->philo[i]->mtr = (*mtr);
		i++;
	}
	return (0);
}
