/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:54:07 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/04 14:07:53 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_break_simulation(t_mtr **mtr)
{
	pthread_mutex_lock(&(*mtr)->stop_simu_mutex);
	if ((*mtr)->stop_simulation == -1)
	{
		pthread_mutex_unlock(&(*mtr)->stop_simu_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&(*mtr)->stop_simu_mutex);
	pthread_mutex_lock(&(*mtr)->stop_eat_mutex);
	if (stop_eat(mtr))
	{
		(*mtr)->stop_eat = 0;
		pthread_mutex_unlock(&(*mtr)->stop_eat_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&(*mtr)->stop_eat_mutex);
	return (0);
}

int	ft_check_philo_died(t_mtr **mtr, int i)
{
	pthread_mutex_lock(&(*mtr)->print_mutex);
	pthread_mutex_lock(&(*mtr)->last_meal_mutex);
	if ((ft_get_current_time() - (*mtr)->philo[i]->last_meal)
		> (*mtr)->philo[i]->time_die)
	{
		pthread_mutex_lock(&(*mtr)->stop_simu_mutex);
		(*mtr)->stop_simulation = -1;
		pthread_mutex_unlock(&(*mtr)->stop_simu_mutex);
		pthread_mutex_unlock(&(*mtr)->print_mutex);
		pthread_mutex_lock(&(*mtr)->print_mutex);
		pthread_mutex_unlock(&(*mtr)->last_meal_mutex);
		printf("%ld %d died\n", ft_get_current_time() - (*mtr)->philo[i]->start,
			(*mtr)->philo[i]->id);
		return (-1);
	}
	pthread_mutex_unlock(&(*mtr)->last_meal_mutex);
	pthread_mutex_unlock(&(*mtr)->print_mutex);
	return (0);
}

void	*monitor_philo(void *arg)
{
	t_mtr	*mtr;
	int		i;

	mtr = (t_mtr *)arg;
	if (mtr->num_philo == 1)
		return (NULL);
	while (1337)
	{
		if (ft_break_simulation(&mtr))
			break ;
		i = 0;
		while (i < mtr->num_philo)
		{
			if (ft_check_philo_died(&mtr, i))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}
