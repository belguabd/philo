/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 15:07:45 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/03 16:04:22 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo_bonus.h"

void	start_simulation(t_data *data)
{
	int	i;
	int	j;

	(1) && (i = 0, j = 0);
	while (i < data->num_philo)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid == -1)
		{
			ft_putendl_fd("fail fork :)", 2);
			while (j < i)
				kill(data->philos[j++].pid, SIGINT);
			exit(EXIT_FAILURE);
		}
		else if (data->philos[i].pid == 0)
		{
			ft_philosopher_routine(&(data->philos[i]));
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	i = 0;
	while (i < data->num_philo)
		if (waitpid(data->philos[i++].pid, NULL, 0) == -1)
			ft_putendl_fd("waitpid failed :)", 2);
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

void	cleanup_semaphores(t_data *data)
{
	sem_close(data->forks);
	sem_unlink("/fork");
	sem_close(data->output_lock);
	sem_unlink("/output_lock");
	sem_close(data->is_alive_lock);
	sem_unlink("/is_alive_lock");
	sem_close(data->stop_eat_lock);
	sem_unlink("/stop_eat_lock");
}

int	main(int argc, char *av[])
{
	t_data	*data;

	if (ft_parsing(av))
		return (ft_putendl_fd("invalid arguments ", 2), 1);
	if (argc < 5)
		return (ft_putendl_fd("invalid arguments ", 2), 1);
	if (argc > 6)
		return (ft_putendl_fd("invalid arguments ", 2), 1);
	init_data(&data, av);
	start_simulation(data);
	cleanup_semaphores(data);
}
