/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:21:46 by guviure           #+#    #+#             */
/*   Updated: 2025/08/28 05:29:52 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

#include "philosopher.h"

static int	usage(int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: %s number_of_philosophers time_to_die "
			"time_to_eat time_to_sleep "
			"[number_of_times_each_philosopher_must_eat]\n",
			argv[0]);
		return (1);
	}
	return (0);
}

static int	start_philos(t_data *data, t_philo **philos, pthread_t *monitor)
{
	int	i;

	*philos = init_philo(data);
	if (!*philos || init_forks_mutex(data))
		return (1);
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_create(&(*philos)[i].thread, NULL,
			philo_routine, &(*philos)[i]);
		i++;
	}
	pthread_create(monitor, NULL, monitor_routine, data);
	return (0);
}

static void	wait_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
		pthread_join(philos[i++].thread, NULL);
}

static void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->stop_mutex);
	free(data->forks);
	free(data->philo);
	free(data);
}

int	main(int argc, char *argv[])
{
	t_data		*data;
	t_philo		*philos;
	pthread_t	monitor;

	if (usage(argc, argv))
		return (1);
	data = init_data(argc, argv);
	if (!data)
		return (1);
	if (data->number_of_philosophers == 1)
		return (handle_single_philo(data));
	if (start_philos(data, &philos, &monitor))
		return (1);
	pthread_join(monitor, NULL);
	wait_threads(data, philos);
	cleanup(data);
	return (0);
}
