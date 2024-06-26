/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:46:12 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/09 17:09:43 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	terminate_all_philos(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (philo->id != data->philos[i].id)
			kill(data->philos[i].pid, SIGINT);
		i++;
	}
	exit(EXIT_FAILURE);
}

void	check_philo_death(t_data *data, t_philo *philo)
{
	if ((ft_get_current_time() - philo->last_meal) > philo->time_die)
	{
		sem_wait(philo->data->output_lock);
		printf("%ld %d %s\n",
			ft_get_current_time() - philo->start, philo->id, "died");
		philo->data->is_alive = false;
		terminate_all_philos(data, philo);
	}
	usleep(100);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	(1) && (philo = (t_philo *)arg, i = 0);
	data = philo->data;
	while (42)
		check_philo_death(data, philo);
	return (NULL);
}

void	philo_routine(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	sem_wait(data->forks);
	print_status(philo, "has taken a fork");
	sem_wait(data->forks);
	print_status(philo, "has taken a fork");
	ft_eat(philo);
	sem_post(data->forks);
	sem_post(data->forks);
	ft_sleep(philo);
	ft_think(philo);
}

void	ft_philosopher_routine(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (pthread_create(&philo->monitor_thread, NULL, monitor, philo))
		ft_putendl_fd("pthread_create failed :)", 2);
	if (data->num_philo == 1)
		return (print_status(philo, "has taken a fork"),
			ft_usleep(philo->time_die, data),
			print_status(philo, "died"));
	if (philo->id % 2 == 0)
		ft_usleep(data->time_to_eat, data);
	while (1337)
	{
		if (philo->stop_eat == philo->data->must_eat_count)
			exit(0);
		philo_routine(philo);
	}
	if (pthread_join(philo->monitor_thread, NULL))
		ft_putendl_fd("pthread_join failed :)", 2);
}
