/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 14:42:33 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/10 10:24:58 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <time.h>
# include <sys/time.h>

typedef struct monitor	t_mtr;
typedef struct philo
{
	pthread_mutex_t	meal_mutex;
	pthread_t		th;
	int				id;
	long			start;
	size_t			time_die;
	int				time_eat;
	int				time_sleep;
	size_t			last_meal;
	int				num_eat;
	t_mtr			*mtr;
	int				must_eat_count;

}	t_philo;
typedef struct monitor
{
	pthread_mutex_t	print_mutex;

	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	num_eat_mutex;
	pthread_mutex_t	*forks;
	pthread_t		thread_monitor;
	t_philo			**philo;
	int				num_philo;
	int				stop_eat;
	int				nbr_each_philo;
	int				philo_ready;
}	t_mtr;

int		ft_atoi_parsing(const char *str);
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_atoi_parsing(const char *str);
void	free_monitor(t_mtr *mtr);
int		init_monitor(t_mtr **mtr, char *av[]);
int		init_mutexes(t_mtr **mtr);
int		init_philosophers(t_mtr **mtr, char *av[]);
int		create_philos(t_mtr **mtr);
void	*monitor_philo(void *arg);
void	*routine(void *arg);
bool	stop_eat(t_mtr **mtr);
size_t	ft_get_current_time(void);
void	ft_usleep(size_t milliseconds);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	print_status(t_philo *philo, char *status);
bool	must_eat(t_mtr *mtr);

#endif