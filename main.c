/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:10:48 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/23 17:28:28 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo *init_philo(t_philo *philo, char *av[])
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->num_philo = ft_atoi(av[1]);
	philo->time_die = ft_atoi(av[2]);
	philo->time_eat = ft_atoi(av[3]);
	philo->time_sleep = ft_atoi(av[4]);
	philo->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	philo->nbr_each_philo = -1;
	if (av[5])
		philo->nbr_each_philo = ft_atoi(av[5]);

	return (philo);
}
size_t ft_get_current_time(void)
{
	struct timeval tv;
	if (gettimeofday(&tv, NULL) == -1)
		ft_putendl_fd("gettimeofday() error", 2);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
int ft_usleep(size_t milliseconds)
{
	size_t start;

	start = ft_get_current_time();
	while ((ft_get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
void ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtr->print_mutex);
	printf("%ld %d is eating\n", ft_get_current_time() - philo->start, philo->id);
	pthread_mutex_unlock(&philo->mtr->print_mutex);
	ft_usleep(philo->time_eat);
}
void ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtr->print_mutex);
	printf("%ld %d is sleeping\n", ft_get_current_time() - philo->start, philo->id);
	pthread_mutex_unlock(&philo->mtr->print_mutex);
	ft_usleep(philo->time_sleep);
}
void ft_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->mtr->print_mutex);
	printf("%ld %d is thinking\n", ft_get_current_time() - philo->start, philo->id);
	pthread_mutex_unlock(&philo->mtr->print_mutex);
}
void ft_die(t_philo *philo)
{
	printf("%ld %d died", philo->start, philo->id);
}
void *routine(void *arg)
{
	int left;
	int right;
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 != 0)
		ft_usleep(philo->time_eat);
	while (1337)
	{
		left = philo->id - 1;
		right = (philo->id) % philo->num_philo;
		pthread_mutex_lock(&philo->mtr->forks[left]);
		pthread_mutex_lock(&philo->mtr->print_mutex);
		printf("%ld %d has taken a fork\n", ft_get_current_time() - philo->start, philo->id);
		pthread_mutex_unlock(&philo->mtr->print_mutex);
		pthread_mutex_lock(&philo->mtr->forks[right]);
		pthread_mutex_lock(&philo->mtr->print_mutex);
		printf("%ld %d has taken a fork\n", ft_get_current_time() - philo->start, philo->id);
		pthread_mutex_unlock(&philo->mtr->print_mutex);
		ft_eat(philo);
		pthread_mutex_unlock(&philo->mtr->forks[left]);
		pthread_mutex_unlock(&philo->mtr->forks[right]);
		ft_sleep(philo);
		ft_think(philo);
	}
	return NULL;
}

int main(int argc, char *av[])
{
	t_mtr *mtr;
	int num_philo;

	int i = 0;
	if (argc < 5)
		ft_putendl_fd("invalid arguments ", 2);
	mtr = (t_mtr *)malloc(sizeof(t_mtr));
	if (!mtr)
		return (0);
	num_philo = ft_atoi(av[1]);
	mtr->philo = (t_philo **)malloc(sizeof(t_philo *) * num_philo);
	mtr->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philo);
	pthread_mutex_init(&mtr->print_mutex, NULL);
	i = 0;
	while (i < num_philo)
		pthread_mutex_init(&mtr->forks[i++], NULL);
	i = 0;
	while (i < num_philo)
	{
		mtr->philo[i] = init_philo(mtr->philo[i], av);
		mtr->philo[i]->id = i + 1;
		mtr->philo[i]->mtr = mtr;
		i++;
	}
	i = 0;
	while (i < num_philo)
	{
		pthread_create(&mtr->philo[i]->th, NULL, &routine, mtr->philo[i]);
		i++;
	}

	i = 0;
	while (i < num_philo)
		pthread_join(mtr->philo[i++]->th, NULL);
	return (0);
}