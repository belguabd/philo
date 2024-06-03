/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:46:12 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/03 15:55:10 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	terminate_all_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
		kill(data->philos[i++].pid, SIGINT);
	exit(EXIT_FAILURE);
}

void	check_philo_death(t_data *data, t_philo *philo)
{
	if (sem_wait(data->last_meal_lock))
		ft_putendl_fd("sem_wait failed :)", 2);
	if ((ft_get_current_time() - philo->last_meal) > philo->time_die)
	{
		if (sem_post(data->last_meal_lock))
			ft_putendl_fd("sem_post failed :)", 2);
		if (sem_wait(philo->data->output_lock))
			ft_putendl_fd("sem_wait failed :)", 2);
		printf("%ld %d %s\n",
			ft_get_current_time() - philo->start, philo->id, "died");
		if (sem_wait(data->is_alive_lock))
			ft_putendl_fd("sem_wait failed :)", 2);
		philo->data->is_alive = false;
		if (sem_post(data->is_alive_lock))
			ft_putendl_fd("sem_post failed :)", 2);
		terminate_all_philos(data);
	}
	if (sem_post(data->last_meal_lock))
		ft_putendl_fd("sem_post failed :)", 2);
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
	if (sem_wait(data->forks))
		ft_putendl_fd("sem_wait failed :)", 2);
	print_status(philo, "has taken a fork");
	if (sem_wait(data->forks))
		ft_putendl_fd("sem_wait failed :)", 2);
	print_status(philo, "has taken a fork");
	ft_eat(philo);
	if (sem_post(data->forks))
		ft_putendl_fd("sem_post failed :)", 2);
	if (sem_post(data->forks))
		ft_putendl_fd("sem_post failed :)", 2);
	ft_sleep(philo);
	ft_think(philo);
}

void	ft_philosopher_routine(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (pthread_create(&philo->monitor_thread, NULL, monitor, philo))
		ft_putendl_fd("pthread_create failed :)", 2);
	philo->start = ft_get_current_time();
	philo->last_meal = ft_get_current_time();
	if (data->num_philo == 1)
		return (print_status(philo, "has taken a fork"),
			print_status(philo, "died"));
	if (philo->id % 2 == 0)
		ft_usleep(data->time_to_eat, data);
	while (1337)
	{
		philo_routine(philo);
		if (philo->stop_eat == philo->data->must_eat_count)
			exit(0);
	}
	if (pthread_join(philo->monitor_thread, NULL))
		ft_putendl_fd("pthread_join failed :)", 2);
}
