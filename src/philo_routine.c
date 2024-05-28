/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 19:51:01 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/28 20:08:47 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_one_philo(t_philo **philo)
{
	if ((*philo)->id % 2 == 0)
		ft_usleep((*philo)->time_eat);
	if ((*philo)->mtr->num_philo == 1)
	{
		printf("%ld %d has taken a fork\n", ft_get_current_time()
			- (*philo)->start, (*philo)->id);
		ft_usleep((*philo)->time_die);
		printf("%ld %d died\n", ft_get_current_time()
			- (*philo)->start, (*philo)->id);
		return (-1);
	}
	return (0);
}

int	stop_simu_routine(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->mtr->stop_simu_mutex);
	if ((*philo)->mtr->stop_simulation == -1)
	{
		pthread_mutex_unlock(&(*philo)->mtr->stop_simu_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&(*philo)->mtr->stop_simu_mutex);
	pthread_mutex_lock(&(*philo)->mtr->stop_eat_mutex);
	if ((*philo)->mtr->stop_eat == 0)
	{
		pthread_mutex_unlock(&(*philo)->mtr->stop_eat_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&(*philo)->mtr->stop_eat_mutex);
	return (0);
}

void	take_fork(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->mtr->forks[(*philo)->id - 1]);
	if (!check_is_died((*philo)->mtr))
	{
		pthread_mutex_lock(&(*philo)->mtr->print_mutex);
		printf("%ld %d has taken a fork\n",
			ft_get_current_time() - (*philo)->start, (*philo)->id);
		pthread_mutex_unlock(&(*philo)->mtr->print_mutex);
	}
	pthread_mutex_lock(&(*philo)->mtr
		->forks[((*philo)->id) % (*philo)->mtr->num_philo]);
	if (!check_is_died((*philo)->mtr))
	{
		pthread_mutex_lock(&(*philo)->mtr->print_mutex);
		printf("%ld %d has taken a fork\n",
			ft_get_current_time() - (*philo)->start, (*philo)->id);
		pthread_mutex_unlock(&(*philo)->mtr->print_mutex);
	}
}

int	philo_take_forks_and_eat(t_philo **philo, int i, int count)
{
	take_fork(&(*philo));
	ft_eat((*philo));
	if (i + count == (*philo)->mtr->nbr_each_philo)
	{
		pthread_mutex_unlock(&(*philo)->mtr
			->forks[((*philo)->id) % (*philo)->mtr->num_philo]);
		pthread_mutex_unlock(&(*philo)->mtr->forks[(*philo)->id - 1]);
		return (-1);
	}
	pthread_mutex_unlock(&(*philo)->mtr
		->forks[((*philo)->id) % (*philo)->mtr->num_philo]);
	pthread_mutex_unlock(&(*philo)->mtr->forks[(*philo)->id - 1]);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		num_meal;
	int		i;
	int		count;

	philo = (t_philo *)arg;
	if (check_one_philo(&philo))
		return (free_monitor(philo->mtr), NULL);
	(1) && (num_meal = 1, i = 0, count = 0);
	if (philo->mtr->nbr_each_philo != -1)
	{
		num_meal = philo->mtr->nbr_each_philo;
		count = 1;
	}
	while (i < num_meal)
	{
		if (stop_simu_routine(&philo))
			return (free_monitor(philo->mtr), NULL);
		if (philo_take_forks_and_eat(&philo, i, count))
			break ;
		ft_sleep(philo);
		ft_think(philo);
		i += count;
	}
	return (NULL);
}
