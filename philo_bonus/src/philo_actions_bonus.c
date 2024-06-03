/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:44:23 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/03 15:55:06 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	print_status(t_philo *philo, const char *status)
{
	if (sem_wait(philo->data->is_alive_lock))
		ft_putendl_fd("sem_wait failed :)", 2);
	if (philo->data->is_alive)
	{
		if (sem_wait(philo->data->output_lock))
			ft_putendl_fd("sem_wait failed :)", 2);
		printf("%ld %d %s\n",
			ft_get_current_time() - philo->start, philo->id, status);
		if (sem_post(philo->data->output_lock))
			ft_putendl_fd("sem_post failed :)", 2);
	}
	if (sem_post(philo->data->is_alive_lock))
		ft_putendl_fd("sem_post failed :)", 2);
}

void	ft_eat(t_philo *philo)
{
	if (sem_wait(philo->data->is_alive_lock))
		ft_putendl_fd("sem_wait failed :)", 2);
	if (philo->data->is_alive)
	{
		if (sem_wait(philo->data->output_lock))
			ft_putendl_fd("sem_wait failed :)", 2);
		printf("%ld %d %s\n",
			ft_get_current_time() - philo->start, philo->id, "is eating");
		if (sem_wait(philo->data->last_meal_lock))
			ft_putendl_fd("sem_wait failed :)", 2);
		philo->last_meal = ft_get_current_time();
		if (sem_post(philo->data->last_meal_lock))
			ft_putendl_fd("sem_post failed :)", 2);
		philo->stop_eat++;
		if (sem_post(philo->data->output_lock))
			ft_putendl_fd("sem_post failed :)", 2);
	}
	if (sem_post(philo->data->is_alive_lock))
		ft_putendl_fd("sem_post failed :)", 2);
	ft_usleep(philo->time_eat, philo->data);
}

void	ft_sleep(t_philo *philo)
{
	if (sem_wait(philo->data->is_alive_lock))
		ft_putendl_fd("sem_wait failed :)", 2);
	if (philo->data->is_alive)
	{
		if (sem_wait(philo->data->output_lock))
			ft_putendl_fd("sem_wait failed :)", 2);
		printf("%ld %d %s\n",
			ft_get_current_time() - philo->start, philo->id, "is sleeping");
		if (sem_post(philo->data->output_lock))
			ft_putendl_fd("sem_post failed :)", 2);
	}
	if (sem_post(philo->data->is_alive_lock))
		ft_putendl_fd("sem_post failed :)", 2);
	ft_usleep(philo->time_sleep, philo->data);
}

void	ft_think(t_philo *philo)
{
	if (sem_wait(philo->data->is_alive_lock))
		ft_putendl_fd("sem_wait failed :)", 2);
	if (philo->data->is_alive)
	{
		if (sem_wait(philo->data->output_lock))
			ft_putendl_fd("sem_wait failed :)", 2);
		printf("%ld %d %s\n",
			ft_get_current_time() - philo->start, philo->id, "is thinking");
		if (sem_post(philo->data->output_lock))
			ft_putendl_fd("sem_post failed :)", 2);
	}
	if (sem_post(philo->data->is_alive_lock))
		ft_putendl_fd("sem_post failed :)", 2);
}
