/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 18:56:10 by guviure           #+#    #+#             */
/*   Updated: 2025/08/25 18:23:33 by guviure          ###   ########.fr       */
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

	start_time = get_time();
	while (1)
	{
		elapsed_time = get_time() - start_time;
		if (elapsed_time >= time_ms)
			break ;
		if (data->someone_is_dead)
			break ;
		usleep(100);
	}
}

void	print_message(t_philo *philo, char	*msg)
{
	long	time;

	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_time() - philo->data->start_time;
	if (!philo->data->someone_is_dead)
		printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
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
