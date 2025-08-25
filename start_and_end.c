/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_and_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 01:08:22 by guviure           #+#    #+#             */
/*   Updated: 2025/08/25 18:27:48 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < data->number_of_philosopher)
	{
		set_last_meal(&data->philo[i], get_time());
		pthread_create(&data->philo[i].thread, NULL,
			ft_routine, &data->philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->number_of_philosopher)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	pthread_join(monitor, NULL);
}

void	end_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosopher)
	{
		pthread_mutex_destroy(&data->forks[i++]);
		pthread_mutex_destroy(&data->philo[i].meal_mutex);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->death_mutex);
	free(data->forks);
	free(data->philo);
}
