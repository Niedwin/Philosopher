/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 01:57:18 by guviure           #+#    #+#             */
/*   Updated: 2025/08/23 01:59:11 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	check_death(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosopher)
	{
		if (get_time() - data->philo[i].last_meal > data->time_to_die)
		{
			print_message(&data->philo[i], "died");
			data->someone_is_dead = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	check_all_ate_enough(t_data *data)
{
	int	i;
	int	all_ate_enough;

	if (data->number_of_meals == -1)
		return (0);
	i = 0;
	all_ate_enough = 1;
	while (i < data->number_of_philosopher)
	{
		if (data->philo[i].meals_eaten < data->number_of_meals)
		{
			all_ate_enough = 0;
			break ;
		}
		i++;
	}
	if (all_ate_enough)
	{
		data->someone_is_dead = 1;
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		if (check_death(data))
			return (NULL);
		if (check_all_ate_enough(data))
			return (NULL);
		usleep(1000);
	}
}
