/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:43:55 by guviure           #+#    #+#             */
/*   Updated: 2025/08/28 05:30:17 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	validate_args(int argc, char *argv[])
{
	int	i;
	int	val;

	i = 1;
	while (i < argc)
	{
		val = atoi(argv[i]);
		if (val <= 0)
		{
			printf("Error: invalid argument (%s)\n", argv[i]);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	setup_data_fields(t_data *data, int argc, char *argv[])
{
	data->number_of_philosophers = atoi(argv[1]);
	data->time_to_die = atol(argv[2]);
	data->time_to_eat = atol(argv[3]);
	data->time_to_sleep = atol(argv[4]);
	data->number_of_times_each_philosopher_must_eat = -1;
	if (argc == 6)
		data->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	data->stop = 0;
	data->start_time = current_time_ms();
	return (0);
}

t_data	*init_data(int argc, char *argv[])
{
	t_data	*data;

	if (validate_args(argc, argv))
		return (NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	setup_data_fields(data, argc, argv);
	data->forks = malloc(sizeof(pthread_mutex_t)
			* data->number_of_philosophers);
	if (!data->forks)
	{
		free(data);
		return (NULL);
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->stop_mutex, NULL);
	return (data);
}

t_philo	*init_philo(t_data *data)
{
	int		i;
	t_philo	*philos;

	philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philos)
		return (NULL);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].last_meal_time = data->start_time;
		philos[i].data = data;
		pthread_mutex_init(&philos[i].meal_mutex, NULL);
		i++;
	}
	data->philo = philos;
	return (philos);
}

int	init_forks_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
}
