/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:01:04 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/09 14:29:10 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_atoi_parsing(const char *str)
{
	int		sign;
	long	res;
	int		i;

	(1) && (i = 0, sign = 1, res = 0);
	while (((str[i] >= 9 && str[i] <= 13) || (str[i] == 32)))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	if (!str[i])
		return (-1);
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - 48) + (res * 10);
		if ((res * sign) > INT_MAX || (res * sign) < INT_MIN)
			return (-1);
		i++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	return (res * sign);
}
