/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:54:07 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/06 15:46:35 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_philos_death(t_mtr *mtr, bool *check_is_died)
{
	int	i;

	i = 0;
	while (i < mtr->num_philo)
	{
		pthread_mutex_lock(&mtr->last_meal_mutex);
		if ((ft_get_current_time() - mtr->philo[i]->last_meal)
			> mtr->philo[i]->time_die)
		{
			pthread_mutex_lock(&mtr->print_mutex);
			*check_is_died = true;
			printf("%ld %d died\n",
				ft_get_current_time() - mtr->philo[i]->start,
				mtr->philo[i]->id);
			pthread_mutex_unlock(&mtr->last_meal_mutex);
			break ;
		}
		pthread_mutex_unlock(&mtr->last_meal_mutex);
		i++;
	}
}

void	*monitor_philo(void *arg)
{
	t_mtr	*mtr;
	bool	check_is_died;

	check_is_died = false;
	mtr = (t_mtr *)arg;
	if (mtr->num_philo == 1)
		return (NULL);
	while (1337)
	{
		if (must_eat(mtr))
			break ;
		check_philos_death(mtr, &check_is_died);
		if (check_is_died)
		{
			free_monitor(mtr);
			break ;
		}
	}
	return (NULL);
}
