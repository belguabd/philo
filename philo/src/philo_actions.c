/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:43:12 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/02 15:20:09 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	ft_get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_putendl_fd("gettimeofday() error", 2);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_mtr *mtr)
{
	size_t	start;

	start = ft_get_current_time();
	while ((ft_get_current_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&mtr->stop_simu_mutex);
		if (mtr->stop_simulation == -1)
		{
			pthread_mutex_unlock(&mtr->stop_simu_mutex);
			return (0);
		}
		pthread_mutex_unlock(&mtr->stop_simu_mutex);
		usleep(500);
	}
	return (0);
}

void	ft_eat(t_philo *philo)
{
	long	current_time;

	if (!check_is_died(philo->mtr))
	{
		current_time = ft_get_current_time();
		pthread_mutex_lock(&philo->mtr->print_mutex);
		printf("%ld %d is eating\n", current_time - philo->start, philo->id);
		philo->last_meal = current_time;
		philo->must_eat_count++;
		if (philo->mtr->nbr_each_philo != -1)
		{
			pthread_mutex_lock(&philo->mtr->num_eat_mutex);
			philo->num_eat++;
			pthread_mutex_unlock(&philo->mtr->num_eat_mutex);
		}
		pthread_mutex_unlock(&philo->mtr->print_mutex);
	}
	ft_usleep(philo->time_eat, philo->mtr);
}

void	ft_sleep(t_philo *philo)
{
	long	current_time;

	if (!check_is_died(philo->mtr))
	{
		current_time = ft_get_current_time();
		pthread_mutex_lock(&philo->mtr->print_mutex);
		printf("%ld %d is sleeping\n", current_time - philo->start, philo->id);
		pthread_mutex_unlock(&philo->mtr->print_mutex);
	}
	ft_usleep(philo->time_sleep, philo->mtr);
}

void	ft_think(t_philo *philo)
{
	long	current_time;

	if (!check_is_died(philo->mtr))
	{
		current_time = ft_get_current_time();
		pthread_mutex_lock(&philo->mtr->print_mutex);
		printf("%ld %d is thinking\n", current_time - philo->start, philo->id);
		pthread_mutex_unlock(&philo->mtr->print_mutex);
	}
}
