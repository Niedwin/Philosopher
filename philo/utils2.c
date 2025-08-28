/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 05:18:07 by guviure           #+#    #+#             */
/*   Updated: 2025/08/28 05:29:38 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	handle_single_philo(t_data *data)
{
	printf("0 1 has taken a fork\n");
	usleep(data->time_to_die * 1000);
	printf("%ld 1 died\n", data->time_to_die);
	free(data->forks);
	free(data);
	return (0);
}

int	check_stop(t_data *data)
{
	int	value;

	pthread_mutex_lock(&data->stop_mutex);
	value = data->stop;
	pthread_mutex_unlock(&data->stop_mutex);
	return (value);
}

void	set_stop(t_data *data)
{
	pthread_mutex_lock(&data->stop_mutex);
	data->stop = 1;
	pthread_mutex_unlock(&data->stop_mutex);
}
