/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belguabd <belguabd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 09:20:57 by belguabd          #+#    #+#             */
/*   Updated: 2024/06/09 19:09:29 by belguabd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>
# include <signal.h>

typedef struct monitor	t_mtr;

typedef struct s_philo
{
	int				id;
	size_t			start;
	size_t			time_die;
	int				time_eat;
	int				time_sleep;
	_Atomic size_t	last_meal;
	int				num_eat;
	pid_t			pid;
	pthread_t		monitor_thread;
	struct s_data	*data;
	int				stop_eat;
}	t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				num_philo;
	int				stop_eat;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	_Atomic bool	is_alive;
	sem_t			*forks;
	sem_t			*output_lock;
}	t_data;

int		ft_atoi_parsing(const char *str);
void	ft_putendl_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
int		ft_atoi_parsing(const char *str);
void	init_data(t_data *data, t_philo *philo, char *av[]);
void	print_status(t_philo *philo, const char *status);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);
void	ft_think(t_philo *philo);
void	ft_philosopher_routine(t_philo *philo);
void	philo_routine(t_philo *philo);
void	*monitor(void *arg);
void	check_philo_death(t_data *data, t_philo *philo);
void	terminate_all_philos(t_data *data, t_philo *philo);
size_t	ft_get_current_time(void);
int		ft_usleep(size_t milliseconds, t_data *data);
#endif