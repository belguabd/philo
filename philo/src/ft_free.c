/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:34:17 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/09 13:49:06 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_free_philos(t_mtr *mtr)
{
	int	i;

	i = 0;
	while (i < mtr->num_philo)
	{
		if (mtr->philo[i])
		{
			pthread_mutex_destroy(&mtr->philo[i]->meal_mutex);
			free(mtr->philo[i]);
		}
		i++;
	}
	free(mtr->philo);
}

void	ft_destroy_mutex(t_mtr *mtr)
{
	pthread_mutex_destroy(&mtr->print_mutex);
	pthread_mutex_destroy(&mtr->num_eat_mutex);
}

void	free_monitor(t_mtr *mtr)
{
	int	i;

	if (mtr)
	{
		if (mtr->philo)
			ft_free_philos(mtr);
		if (mtr->forks)
		{
			i = 0;
			while (i < mtr->num_philo)
				pthread_mutex_destroy(&mtr->forks[i++]);
			free(mtr->forks);
		}
		ft_destroy_mutex(mtr);
		free(mtr);
	}
}
