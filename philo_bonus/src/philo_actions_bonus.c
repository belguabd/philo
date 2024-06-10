/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:44:23 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/09 17:08:14 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	print_status(t_philo *philo, const char *status)
{
	sem_wait(philo->data->output_lock);
	printf("%ld %d %s\n",
		ft_get_current_time() - philo->start, philo->id, status);
	sem_post(philo->data->output_lock);
}

void	ft_eat(t_philo *philo)
{
	print_status(philo, "is eating");
	philo->last_meal = ft_get_current_time();
	philo->stop_eat++;
	ft_usleep(philo->time_eat, philo->data);
}

void	ft_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->time_sleep, philo->data);
}

void	ft_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}
