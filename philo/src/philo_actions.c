/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:43:12 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/06 15:45:06 by belguabd         ###   ########.fr       */
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

void	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_get_current_time();
	while ((ft_get_current_time() - start) < milliseconds)
		usleep(250);
}

void	ft_eat(t_philo *philo)
{
	long	current_time;

	current_time = ft_get_current_time();
	print_status(philo, "is eating");
	pthread_mutex_lock(&philo->mtr->last_meal_mutex);
	philo->last_meal = current_time;
	pthread_mutex_unlock(&philo->mtr->last_meal_mutex);
	if (philo->num_eat > 0)
		philo->num_eat--;
	ft_usleep(philo->time_eat);
}

void	ft_sleep(t_philo *philo)
{
	long	current_time;

	current_time = ft_get_current_time();
	print_status(philo, "is sleeping");
	ft_usleep(philo->time_sleep);
}

void	ft_think(t_philo *philo)
{
	long	current_time;

	current_time = ft_get_current_time();
	print_status(philo, "is thinking");
}
