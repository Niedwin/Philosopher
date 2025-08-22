/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 00:06:24 by guviure           #+#    #+#             */
/*   Updated: 2025/08/23 00:07:32 by guviure          ###   ########.fr       */
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


typedef struct s_data
{
	int				number_of_philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_hungry;
	int				number_of_meals;
	long			start_time;
	int				someone_is_dead;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}	t_data;

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

int	ft_atoi(const char *str);
int	init_mutex_and_philos(t_data *data);

#endif