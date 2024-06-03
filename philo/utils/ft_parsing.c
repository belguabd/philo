/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:01:04 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/28 20:08:59 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_check_sign(char c)
{
	if (c == '-' || c == '+')
		return (-1);
	return (0);
}

long	ft_atoi_parsing(char *str)
{
	long	res;
	int		i;

	i = 0;
	res = 0;
	while (str[i] >= 9 && str[i] <= 13)
		return (-1);
	while (str[i] == 32)
		i++;
	if (ft_check_sign(str[i]))
		return (-1);
	if (!str[i])
		return (-1);
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = (str[i++] - 48) + (res * 10);
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	return (res);
}
