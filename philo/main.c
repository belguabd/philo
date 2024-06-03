/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:10:48 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/02 15:16:20 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

int	check_is_died(t_mtr *mtr)
{
	int	result;

	pthread_mutex_lock(&mtr->stop_simu_mutex);
	pthread_mutex_lock(&mtr->check_is_died);
	if (!mtr->stop_simulation)
		result = 0;
	else
		result = -1;
	pthread_mutex_unlock(&mtr->check_is_died);
	pthread_mutex_unlock(&mtr->stop_simu_mutex);
	return (result);
}

bool	stop_eat(t_mtr **mtr)
{
	int	i;

	i = 0;
	while (i < (*mtr)->num_philo)
	{
		pthread_mutex_lock(&(*mtr)->num_eat_mutex);
		if ((*mtr)->nbr_each_philo == -1)
			(*mtr)->philo[i]->num_eat = -2;
		if ((*mtr)->philo[i]->num_eat < (*mtr)->nbr_each_philo)
		{
			pthread_mutex_unlock(&(*mtr)->num_eat_mutex);
			return (false);
		}
		pthread_mutex_unlock(&(*mtr)->num_eat_mutex);
		i++;
	}
	return (true);
}

int	join_threads(t_mtr **mtr)
{
	int	i;

	i = 0;
	while (i < (*mtr)->num_philo)
	{
		if (pthread_detach((*mtr)->philo[i]->th))
			return (-1);
		i++;
	}
	if (pthread_join((*mtr)->thread_monitor, NULL))
		return (-1);
	return (0);
}

int	ft_parsing(char *av[])
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (ft_atoi_parsing(av[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	main(int argc, char *av[])
{
	t_mtr	*mtr;

	if (ft_parsing(av))
		return (ft_putendl_fd("invalid arguments ", 2), 1);
	if (argc < 5)
		return (ft_putendl_fd("invalid arguments ", 2), 1);
	if (argc > 6)
		return (ft_putendl_fd("invalid arguments ", 2), 1);
	if (init_monitor(&mtr, av))
		return (free_monitor(mtr), -1);
	if (init_mutexes(&mtr))
		return (free_monitor(mtr), -1);
	if (init_philosophers(&mtr, av))
		return (free_monitor(mtr), -1);
	if (create_philos(&mtr))
		return (free_monitor(mtr), -1);
	if (join_threads(&mtr))
		return (free_monitor(mtr), -1);
	free_monitor(mtr);
	return (0);
}
