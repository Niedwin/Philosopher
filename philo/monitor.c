/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 01:22:39 by guviure           #+#    #+#             */
/*   Updated: 2025/08/28 05:25:27 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!check_stop(data))
	{
		i = 0;
		while (i < data->number_of_philosophers)
		{
			pthread_mutex_lock(&data->philo[i].meal_mutex);
			if (current_time_ms() - data->philo[i].last_meal_time
				> data->time_to_die)
			{
				pthread_mutex_unlock(&data->philo[i].meal_mutex);
				print_status(&data->philo[i], "died");
				set_stop(data);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].meal_mutex);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		precise_sleep(philo->data->time_to_eat / 2);
	while (!check_stop(philo->data))
	{
		philo_eat(philo);
		if (check_stop(philo->data))
			break ;
		philo_sleep(philo);
		if (check_stop(philo->data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
