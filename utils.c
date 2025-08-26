/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:56:10 by guviure           #+#    #+#             */
/*   Updated: 2025/08/27 00:20:58 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	smart_sleep(long time_ms, t_data *data)
{
	long	start_time;
	long	elapsed_time;
	int		is_dead;

	start_time = get_time();
	while (1)
	{
		pthread_mutex_lock(&data->death_mutex);
		is_dead = data->someone_is_dead;
		pthread_mutex_unlock(&data->death_mutex);
		if (is_dead)
			break ;
		elapsed_time = get_time() - start_time;
		if (elapsed_time >= time_ms)
			break ;
		usleep(100);
	}
}

void	print_message(t_philo *philo, char	*msg)
{
	long	time;

	pthread_mutex_lock(&philo->data->death_mutex);
	if (!philo->data->someone_is_dead)
	{
		time = get_time() - philo->data->start_time;
		printf("%ld %d %s\n", time, philo->id, msg);
	}
	pthread_mutex_unlock(&philo->data->death_mutex);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}
