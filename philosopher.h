/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:06:24 by guviure           #+#    #+#             */
/*   Updated: 2025/08/23 01:36:08 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	long			last_meal;
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	int				number_of_philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	long			start_time;
	int				someone_is_dead;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_data;

int		ft_atoi(const char *str);
int		init_mutex(t_data *data);
int		init_philosophers(t_data *data);
int		parse_args(int argc, char **argv, t_data *data);
int		init_all(t_data *data);
void	start_simulation(t_data *data);
void	end_simulation(t_data *data);
long	get_time(void);
void	print_message(t_philo *philo, char *msg);
void	smart_sleep(long time_ms, t_data *data);
void	*philo_routine(void *arg);
void	*monitor_routine(void *arg);
void	*ft_routine(void *arg);

#endif