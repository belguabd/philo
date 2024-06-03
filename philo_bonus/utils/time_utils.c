/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:54:34 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/03 16:05:17 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

size_t	ft_get_current_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		ft_putendl_fd("gettimeofday() error", 2);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds, t_data *data)
{
	size_t	start;

	start = ft_get_current_time();
	while ((ft_get_current_time() - start) < milliseconds)
	{
		sem_wait(data->is_alive_lock);
		if (data->is_alive == false)
		{
			sem_post(data->is_alive_lock);
			return (0);
		}
		sem_post(data->is_alive_lock);
		usleep(500);
	}
	return (0);
}
