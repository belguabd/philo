/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:51:01 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/06 15:48:29 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_one_philo(t_philo *philo)
{
	printf("%ld %d has taken a fork\n",
		ft_get_current_time() - philo->start, philo->id);
	ft_usleep(philo->time_die);
	printf("%ld %d died\n",
		ft_get_current_time() - philo->start, philo->id);
}

void	print_status(t_philo *philo, char *status)
{
	pthread_mutex_lock(&philo->mtr->print_mutex);
	printf("%ld %d %s\n",
		ft_get_current_time() - philo->start,
		philo->id, status);
	pthread_mutex_unlock(&philo->mtr->print_mutex);
}

bool	must_eat(t_mtr *mtr)
{
	int	i;

	i = 0;
	while (i < mtr->num_philo)
	{
		if (mtr->philo[i]->num_eat != 0)
			return (false);
		i++;
	}
	return (true);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		nbr_ph;

	philo = (t_philo *)arg;
	nbr_ph = philo->mtr->num_philo;
	if (nbr_ph == 1)
		return (check_one_philo(philo), NULL);
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_eat);
	while (1337)
	{
		if (must_eat(philo->mtr))
			break ;
		pthread_mutex_lock(&philo->mtr->forks[philo->id - 1]);
		pthread_mutex_lock(&philo->mtr->forks[philo->id % nbr_ph]);
		print_status(philo, "has taken a fork");
		print_status(philo, "has taken a fork");
		ft_eat(philo);
		pthread_mutex_unlock(&philo->mtr->forks[philo->id - 1]);
		pthread_mutex_unlock(&philo->mtr->forks[philo->id % nbr_ph]);
		ft_sleep(philo);
		ft_think(philo);
	}
	return (NULL);
}
