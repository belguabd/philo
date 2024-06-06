/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:41:59 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/04 16:18:39 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	init_semaphores(t_data *data, t_philo *philos, int num_philo)
{
	sem_unlink("/fork");
	sem_unlink("/output_lock");
	sem_unlink("/is_alive_lock");
	sem_unlink("/stop_eat_lock");
	sem_unlink("/last_meal_lock");
	data->forks = sem_open("/fork", O_CREAT, 0644, num_philo);
	if (data->forks == SEM_FAILED)
		ft_putendl_fd("fail sem_open", 2);
	data->output_lock = sem_open("/output_lock", O_CREAT, 0644, 1);
	if (data->output_lock == SEM_FAILED)
		ft_putendl_fd("fail sem_open", 2);
	data->last_meal_lock = sem_open("/last_meal_lock", O_CREAT, 0644, 1);
	if (data->last_meal_lock == SEM_FAILED)
		ft_putendl_fd("fail sem_open", 2);
	data->is_alive_lock = sem_open("/is_alive_lock", O_CREAT, 0644, 1);
	if (data->is_alive_lock == SEM_FAILED)
		ft_putendl_fd("fail sem_open", 2);
	data->stop_eat_lock = sem_open("/stop_eat_lock", O_CREAT, 0644, 1);
	if (data->stop_eat_lock == SEM_FAILED)
		ft_putendl_fd("fail sem_open", 2);
	data->philos = philos;
}

void	ft_init_data(t_data *data, char *av[])
{
	int	num_philo;

	num_philo = ft_atoi(av[1]);
	data->num_philo = num_philo;
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->must_eat_count = ft_atoi(av[5]);
	else
		data->must_eat_count = -1;
	data->stop_eat = 0;
	data->stop_simulation = 0;
	data->is_alive = true;
}

void	init_philos(t_data *data)
{
	size_t	current_time;
	int		i;

	current_time = ft_get_current_time();
	i = 0;
	while (i < data->num_philo)
	{
		data->philos[i].id = i + 1;
		data->philos[i].start = current_time;
		data->philos[i].time_die = data->time_to_die;
		data->philos[i].time_eat = data->time_to_eat;
		data->philos[i].time_sleep = data->time_to_sleep;
		data->philos[i].last_meal = current_time;
		data->philos[i].num_eat = 0;
		data->philos[i].pid = 0;
		data->philos[i].stop_eat = 0;
		data->philos[i].data = data;
		i++;
	}
}

void	init_data(t_data *data, t_philo *philos, char *av[])
{
	int	num_philo;

	num_philo = ft_atoi(av[1]);
	ft_init_data(data, av);
	init_semaphores(data, philos, num_philo);
	init_philos(data);
}
