/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:10:48 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/27 14:59:30 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_is_died(t_mtr *mtr)
{
	int result;

	pthread_mutex_lock(&mtr->stop_simu_mutex);
	pthread_mutex_lock(&mtr->check_is_died);
	if (!mtr->stop_simulation)
		result = 0;
	else
		result = -1;
	pthread_mutex_unlock(&mtr->check_is_died);
	pthread_mutex_unlock(&mtr->stop_simu_mutex);
	return result;
}

t_philo *init_philo(t_philo *philo, char *av[])
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->time_die = ft_atoi(av[2]);
	philo->time_eat = ft_atoi(av[3]);
	philo->time_sleep = ft_atoi(av[4]);
	philo->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	philo->last_meal = philo->start;
	philo->num_eat = 0;
	pthread_mutex_init(&philo->meal_mutex, NULL);

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
	long current_time;

	if (!check_is_died(philo->mtr))
	{
		current_time = ft_get_current_time();
		pthread_mutex_lock(&philo->mtr->print_mutex);
		printf("%ld %d is eating\n", current_time - philo->start, philo->id);
		philo->last_meal = current_time;
		if (philo->mtr->nbr_each_philo != -1)
		{
			pthread_mutex_lock(&philo->mtr->num_eat_mutex);
			philo->num_eat++;
			pthread_mutex_unlock(&philo->mtr->num_eat_mutex);
		}
		else
		{
			pthread_mutex_lock(&philo->mtr->num_eat_mutex);
			philo->num_eat = -2;
			pthread_mutex_unlock(&philo->mtr->num_eat_mutex);
		}
		pthread_mutex_unlock(&philo->mtr->print_mutex);
	}
	ft_usleep(philo->time_eat);
}
void ft_sleep(t_philo *philo)
{
	long current_time;

	if (!check_is_died(philo->mtr))
	{
		current_time = ft_get_current_time();
		pthread_mutex_lock(&philo->mtr->print_mutex);
		printf("%ld %d is sleeping\n", current_time - philo->start, philo->id);
		pthread_mutex_unlock(&philo->mtr->print_mutex);
	}
	ft_usleep(philo->time_sleep);
}
void ft_think(t_philo *philo)
{
	long current_time;

	if (!check_is_died(philo->mtr))
	{
		current_time = ft_get_current_time();
		pthread_mutex_lock(&philo->mtr->print_mutex);
		printf("%ld %d is thinking\n", current_time - philo->start, philo->id);
		pthread_mutex_unlock(&philo->mtr->print_mutex);
	}
}
void ft_wait_all_philos(t_philo *philo)
{
	int a = 0;
	pthread_mutex_lock(&philo->mtr->wait_philos);
	philo->mtr->philo_ready += 1;
	while (philo->mtr->philo_ready != philo->mtr->num_philo)
	{
		pthread_mutex_unlock(&philo->mtr->wait_philos);
		a++;
		pthread_mutex_lock(&philo->mtr->wait_philos);
	}
	pthread_mutex_unlock(&philo->mtr->wait_philos);
}
void *routine(void *arg)
{
	int left;
	int right;

	t_philo *philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->time_eat);
	if (philo->mtr->num_philo == 1)
	{
		printf("%ld %d has taken a fork\n", ft_get_current_time() - philo->start, philo->id);
		ft_usleep(philo->time_die);
		printf("%ld %d died\n", ft_get_current_time() - philo->start, philo->id);
		return (NULL);
	}
	int num_meal = 1;
	int i = 0;
	int count = 0;
	if (philo->mtr->nbr_each_philo != -1)
	{
		num_meal = philo->mtr->nbr_each_philo;
		count = 1;
	}

	while (i < num_meal)
	{
		pthread_mutex_lock(&philo->mtr->stop_simu_mutex);
		if (philo->mtr->stop_simulation == -1)
		{
			pthread_mutex_unlock(&philo->mtr->stop_simu_mutex);
			break;
		}
		pthread_mutex_unlock(&philo->mtr->stop_simu_mutex);
		pthread_mutex_lock(&philo->mtr->stop_eat_mutex);
		if (philo->mtr->stop_eat == 0)
		{
			pthread_mutex_unlock(&philo->mtr->stop_eat_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mtr->stop_eat_mutex);
		left = philo->id - 1;
		right = (philo->id) % philo->mtr->num_philo;
		pthread_mutex_lock(&philo->mtr->forks[left]);
		if (!check_is_died(philo->mtr))
		{
			pthread_mutex_lock(&philo->mtr->print_mutex);
			printf("%ld %d has taken a fork\n", ft_get_current_time() - philo->start, philo->id);
			pthread_mutex_unlock(&philo->mtr->print_mutex);
		}
		pthread_mutex_lock(&philo->mtr->forks[right]);
		if (!check_is_died(philo->mtr))
		{
			pthread_mutex_lock(&philo->mtr->print_mutex);
			printf("%ld %d has taken a fork\n", ft_get_current_time() - philo->start, philo->id);
			pthread_mutex_unlock(&philo->mtr->print_mutex);
		}
		ft_eat(philo);
		if (i + count == philo->mtr->nbr_each_philo)
		{
			pthread_mutex_unlock(&philo->mtr->forks[right]);
			pthread_mutex_unlock(&philo->mtr->forks[left]);
			break;
		}
		pthread_mutex_unlock(&philo->mtr->forks[right]);
		pthread_mutex_unlock(&philo->mtr->forks[left]);
		ft_sleep(philo);
		ft_think(philo);
		i += count;
	}
	return (NULL);
}

bool stop_eat(t_mtr *mtr)
{
	int i = 0;
	while (i < mtr->num_philo)
	{
		pthread_mutex_lock(&mtr->num_eat_mutex);
		if (mtr->philo[i]->num_eat < mtr->nbr_each_philo)
		{
			pthread_mutex_unlock(&mtr->num_eat_mutex);
			return (false);
		}
		pthread_mutex_unlock(&mtr->num_eat_mutex);
		i++;
	}
	return (true);
}
void *monitor_philo(void *arg)
{
	t_mtr *mtr = (t_mtr *)arg;
	int i = 0;
	if (mtr->num_philo == 1)
	{
		return (NULL);
	}

	while (1337)
	{
		pthread_mutex_lock(&mtr->stop_simu_mutex);
		if (mtr->stop_simulation == -1)
		{
			pthread_mutex_unlock(&mtr->stop_simu_mutex);
			break;
		}
		pthread_mutex_unlock(&mtr->stop_simu_mutex);
		pthread_mutex_lock(&mtr->stop_eat_mutex);
		if (stop_eat(mtr))
		{
			mtr->stop_eat = 0;
			pthread_mutex_unlock(&mtr->stop_eat_mutex);
			return (NULL);
		}
		pthread_mutex_unlock(&mtr->stop_eat_mutex);
		i = 0;
		while (i < mtr->num_philo)
		{
			pthread_mutex_lock(&mtr->print_mutex);
			if ((ft_get_current_time() - mtr->philo[i]->last_meal) >= mtr->philo[i]->time_die)
			{

				pthread_mutex_lock(&mtr->stop_simu_mutex);
				mtr->stop_simulation = -1;
				pthread_mutex_unlock(&mtr->stop_simu_mutex);
				pthread_mutex_unlock(&mtr->print_mutex);
				pthread_mutex_lock(&mtr->print_mutex);
				printf("%ld %d died\n", ft_get_current_time() - mtr->philo[i]->start, mtr->philo[i]->id);
				return (NULL);
			}
			pthread_mutex_unlock(&mtr->print_mutex);
			i++;
		}
	}
	return (NULL);
}

int main(int argc, char *av[])
{
	t_mtr *mtr;
	int num_philo;

	int i = 0;
	if (argc < 5)
		ft_putendl_fd("invalid arguments ", 2);
	mtr = (t_mtr *)malloc(sizeof(t_mtr));
	num_philo = ft_atoi(av[1]);
	if (!mtr)
		return (0);
	mtr->philo = (t_philo **)malloc(sizeof(t_philo *) * num_philo);
	mtr->stop_simulation = 0;
	mtr->num_philo = num_philo;
	mtr->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philo);
	pthread_mutex_init(&mtr->print_mutex, NULL);
	pthread_mutex_init(&mtr->check_is_died, NULL);
	pthread_mutex_init(&mtr->stop_simu_mutex, NULL);
	pthread_mutex_init(&mtr->stop_eat_mutex, NULL);
	pthread_mutex_init(&mtr->num_eat_mutex, NULL);
	pthread_mutex_init(&mtr->wait_philos, NULL);
	mtr->stop_eat = -2;
	if (av[5])
		mtr->nbr_each_philo = ft_atoi(av[5]);
	else
		mtr->nbr_each_philo = -1;
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
	pthread_t thread_monitor;
	pthread_create(&thread_monitor, NULL, &monitor_philo, mtr);
	i = 0;
	while (i < num_philo)
	{
		pthread_join(mtr->philo[i]->th, NULL);
		i++;
	}
	pthread_join(thread_monitor, NULL);
	return (0);
}