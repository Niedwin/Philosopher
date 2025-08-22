/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialisation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:55:52 by guviure           #+#    #+#             */
/*   Updated: 2025/08/23 00:22:11 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	init_mutex_and_philos(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosopher);
	data->philo = malloc(sizeof(t_philo) * data->number_of_philosopher);
	if (!data->forks || !data->philo)
		return (0);
	while (i < data->number_of_philosopher)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (0);
	i = 0;
	while (i < data->number_of_philosopher)
	{
		data->philo[i].id = i + 1;
		data->philo[i].meals_eaten = 0;
		data->philo[i].last_meal = 0;
		data->philo[i].data = data;
		data->philo[i].left_fork = &data->forks[i];
		data->philo[i].right_fork = &data->forks[(i + 1) % data->number_of_philosopher];
		i++;
	}
	return (1);
}

int init_all(t_data *data)
{
    if (!init_mutex_and_philos(data))
    {
        printf("Error: Mutex initialization failed\n");
        return (0);
    }
    return (1);
}