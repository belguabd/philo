/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:01:04 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/28 20:08:56 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	int					sign;
	unsigned long long	res;
	int					i;

	i = 0;
	sign = 1;
	res = 0;
	while (((str[i] >= 9 && str[i] <= 13) || (str[i] == 32)))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - 48) + (res * 10);
		if (res > 9223372036854775807)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		i++;
	}
	return (res * sign);
}
