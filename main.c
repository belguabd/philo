/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:10:48 by belguabd          #+#    #+#             */
/*   Updated: 2024/05/28 13:10:18 by belguabd         ###   ########.fr       */
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

	if (gettimeofday(&tv, NULL) == -1)
		return (NULL);
	philo = (t_philo *)malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->time_die = ft_atoi(av[2]);
	philo->time_eat = ft_atoi(av[3]);
	philo->time_sleep = ft_atoi(av[4]);
	philo->start = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	philo->last_meal = philo->start;
	philo->num_eat = 0;
	if (pthread_mutex_init(&philo->meal_mutex, NULL))
		return (NULL);
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
int check_one_philo(t_philo **philo)
{
	if ((*philo)->id % 2 == 0)
		ft_usleep((*philo)->time_eat);
	if ((*philo)->mtr->num_philo == 1)
	{
		printf("%ld %d has taken a fork\n", ft_get_current_time() - (*philo)->start, (*philo)->id);
		ft_usleep((*philo)->time_die);
		printf("%ld %d died\n", ft_get_current_time() - (*philo)->start, (*philo)->id);
		return (-1);
	}
	return (0);
}
int stop_simu_routine(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->mtr->stop_simu_mutex);
	if ((*philo)->mtr->stop_simulation == -1)
	{
		pthread_mutex_unlock(&(*philo)->mtr->stop_simu_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&(*philo)->mtr->stop_simu_mutex);
	pthread_mutex_lock(&(*philo)->mtr->stop_eat_mutex);
	if ((*philo)->mtr->stop_eat == 0)
	{
		pthread_mutex_unlock(&(*philo)->mtr->stop_eat_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&(*philo)->mtr->stop_eat_mutex);
	return (0);
}
void take_fork(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->mtr->forks[(*philo)->id - 1]);
	if (!check_is_died((*philo)->mtr))
	{
		pthread_mutex_lock(&(*philo)->mtr->print_mutex);
		printf("%ld %d has taken a fork\n",
			   ft_get_current_time() - (*philo)->start, (*philo)->id);
		pthread_mutex_unlock(&(*philo)->mtr->print_mutex);
	}
	pthread_mutex_lock(&(*philo)->mtr->forks[((*philo)->id) % (*philo)->mtr->num_philo]);
	if (!check_is_died((*philo)->mtr))
	{
		pthread_mutex_lock(&(*philo)->mtr->print_mutex);
		printf("%ld %d has taken a fork\n",
			   ft_get_current_time() - (*philo)->start, (*philo)->id);
		pthread_mutex_unlock(&(*philo)->mtr->print_mutex);
	}
}
int philo_take_forks_and_eat(t_philo **philo, int i, int count)
{
	take_fork(&(*philo));
	ft_eat((*philo));
	if (i + count == (*philo)->mtr->nbr_each_philo)
	{
		pthread_mutex_unlock(&(*philo)->mtr->forks[((*philo)->id) % (*philo)->mtr->num_philo]);
		pthread_mutex_unlock(&(*philo)->mtr->forks[(*philo)->id - 1]);
		return (-1);
	}
	pthread_mutex_unlock(&(*philo)->mtr->forks[((*philo)->id) % (*philo)->mtr->num_philo]);
	pthread_mutex_unlock(&(*philo)->mtr->forks[(*philo)->id - 1]);
	return (0);
}
void *routine(void *arg)
{
	t_philo *philo;
	int num_meal;
	int i;
	int count;

	philo = (t_philo *)arg;
	if (check_one_philo(&philo))
		return (NULL);
	(1) && (num_meal = 1, i = 0, count = 0);
	if (philo->mtr->nbr_each_philo != -1)
	{
		num_meal = philo->mtr->nbr_each_philo;
		count = 1;
	}
	while (i < num_meal)
	{
		if (stop_simu_routine(&philo))
			return (NULL);
		if (philo_take_forks_and_eat(&philo, i, count))
			break;
		ft_sleep(philo);
		ft_think(philo);
		i += count;
	}
	return (NULL);
}
bool stop_eat(t_mtr **mtr)
{
	int i = 0;
	while (i < (*mtr)->num_philo)
	{
		pthread_mutex_lock(&(*mtr)->num_eat_mutex);
		if ((*mtr)->nbr_each_philo == -1)
			(*mtr)->philo[i]->num_eat = -2;
		if ((*mtr)->philo[i]->num_eat < (*mtr)->nbr_each_philo)
		{
			pthread_mutex_unlock(&(*mtr)->num_eat_mutex);
			return (false);
		}
		pthread_mutex_unlock(&(*mtr)->num_eat_mutex);
		i++;
	}
	return (true);
}
int ft_break_simulation(t_mtr **mtr)
{
	pthread_mutex_lock(&(*mtr)->stop_simu_mutex);
	if ((*mtr)->stop_simulation == -1)
	{
		pthread_mutex_unlock(&(*mtr)->stop_simu_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&(*mtr)->stop_simu_mutex);
	pthread_mutex_lock(&(*mtr)->stop_eat_mutex);
	if (stop_eat(mtr))
	{
		(*mtr)->stop_eat = 0;
		pthread_mutex_unlock(&(*mtr)->stop_eat_mutex);
		return (-1);
	}
	pthread_mutex_unlock(&(*mtr)->stop_eat_mutex);
	return (0);
}
int ft_check_philo_died(t_mtr **mtr, int i)
{
	pthread_mutex_lock(&(*mtr)->print_mutex);
	if ((ft_get_current_time() - (*mtr)->philo[i]->last_meal) >=
		(*mtr)->philo[i]->time_die)
	{
		pthread_mutex_lock(&(*mtr)->stop_simu_mutex);
		(*mtr)->stop_simulation = -1;
		pthread_mutex_unlock(&(*mtr)->stop_simu_mutex);
		pthread_mutex_unlock(&(*mtr)->print_mutex);
		pthread_mutex_lock(&(*mtr)->print_mutex);
		printf("%ld %d died\n", ft_get_current_time() - (*mtr)->philo[i]->start,
			   (*mtr)->philo[i]->id);
		return (-1);
	}
	pthread_mutex_unlock(&(*mtr)->print_mutex);
	return (0);
}
void *monitor_philo(void *arg)
{
	t_mtr *mtr;
	int i;

	mtr = (t_mtr *)arg;
	if (mtr->num_philo == 1)
		return (NULL);
	while (1337)
	{
		if (ft_break_simulation(&mtr))
			break;
		i = 0;
		while (i < mtr->num_philo)
		{
			if (ft_check_philo_died(&mtr, i))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

int init_monitor(t_mtr **mtr, char *av[])
{
	int num_philo;

	(*mtr) = (t_mtr *)malloc(sizeof(t_mtr));
	if (!mtr)
		return (-1);
	num_philo = ft_atoi(av[1]);
	(*mtr)->philo = (t_philo **)malloc(sizeof(t_philo *) * num_philo);
	if (!(*mtr)->philo)
		return (-1);
	(*mtr)->stop_simulation = 0;
	(*mtr)->num_philo = num_philo;
	(*mtr)->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * num_philo);
	if (!(*mtr)->forks)
		return (-1);
	(*mtr)->philo_ready = 0;
	(*mtr)->stop_eat = -2;
	if (av[5])
		(*mtr)->nbr_each_philo = ft_atoi(av[5]);
	else
		(*mtr)->nbr_each_philo = -1;
	return (0);
}
int init_philosophers(t_mtr **mtr, char *av[])
{
	t_philo *philo;
	int i;

	i = 0;
	while (i < (*mtr)->num_philo)
	{
		philo = init_philo((*mtr)->philo[i], av);
		if (!philo)
			return (-1);
		(*mtr)->philo[i] = philo;
		(*mtr)->philo[i]->id = i + 1;
		(*mtr)->philo[i]->mtr = (*mtr);
		i++;
	}
	return (0);
}
int init_mutexes(t_mtr **mtr)
{
	int i;

	i = 0;
	while (i < (*mtr)->num_philo)
		if (pthread_mutex_init(&(*mtr)->forks[i++], NULL))
			return (-1);
	if (pthread_mutex_init(&(*mtr)->print_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&(*mtr)->check_is_died, NULL))
		return (-1);
	if (pthread_mutex_init(&(*mtr)->stop_simu_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&(*mtr)->stop_eat_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&(*mtr)->num_eat_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&(*mtr)->wait_philos, NULL))
		return (-1);
	return (0);
}
int create_philos(t_mtr **mtr)
{
	int i;

	i = 0;
	while (i < (*mtr)->num_philo)
	{
		if (pthread_create(&(*mtr)->philo[i]->th, NULL,
						   &routine, (*mtr)->philo[i]))
			return (-1);
		i++;
	}
	if (pthread_create(&(*mtr)->thread_monitor, NULL,
					   &monitor_philo, (*mtr)))
		return (-1);
	return (0);
}
int join_threads(t_mtr **mtr)
{
	int i;

	i = 0;
	while (i < (*mtr)->num_philo)
	{
		if (pthread_join((*mtr)->philo[i]->th, NULL))
			return (-1);
		i++;
	}
	if (pthread_join((*mtr)->thread_monitor, NULL))
		return (-1);
	return (0);
}
int ft_parsing(char *av[])
{
	int i;
	i = 1;
	while (av[i])
	{
		if (ft_atoi_parsing(av[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}
void f()
{
	system("leaks philo");
}
void free_monitor(t_mtr *mtr)
{
	int i;
	if (mtr)
	{
		if (mtr->philo)
		{
			i = 0;
			while (i < mtr->num_philo)
			{
				if (mtr->philo[i])
					free(mtr->philo[i]);
				i++;
			}
			free(mtr->philo);
		}
		if (mtr->forks)
			free(mtr->forks);
		free(mtr);
	}
}
int main(int argc, char *av[])
{
	t_mtr *mtr;
	atexit(f);
	if (ft_parsing(av))
		return (ft_putendl_fd("invalid arguments ", 2), 1);
	if (argc < 5)
		return (ft_putendl_fd("invalid arguments ", 2), 1);
	if (argc > 6)
		return (ft_putendl_fd("invalid arguments ", 2), 1);
	if (init_monitor(&mtr, av))
		return (free_monitor(mtr), 1);
	if (init_mutexes(&mtr))
		return (free_monitor(mtr), 1);
	if (init_philosophers(&mtr, av))
		return (free_monitor(mtr), 1);
	if (create_philos(&mtr))
		return (free_monitor(mtr), 1);
	if (join_threads(&mtr))
		return (free_monitor(mtr), 1);
	return (0);
}
