/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:22:11 by guviure           #+#    #+#             */
/*   Updated: 2025/08/28 05:27:01 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct s_philo
{
	int				id;
	int				meals_eaten;
	long long		last_meal_time;
	pthread_t		thread;
	t_data			*data;
	pthread_mutex_t	meal_mutex;
};

struct s_data
{
	int				number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				stop;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	t_philo			*philo;
};

long long	current_time_ms(void);
void		precise_sleep(long long ms);
int			ft_atoi(const char *str);
void		print_status(t_philo *philo, char *action);
t_data		*init_data(int argc, char *argv[]);
t_philo		*init_philo(t_data *data);
int			init_forks_mutex(t_data *data);
void		take_forks(t_philo *philo);
void		release_forks(t_philo *philo);
void		philo_eat(t_philo *philo);
void		philo_sleep(t_philo *philo);
void		philo_think(t_philo *philo);
void		*philo_routine(void *arg);
void		*monitor_routine(void *arg);
int			check_stop(t_data *data);
void		set_stop(t_data *data);
int			handle_single_philo(t_data *data);

#endif