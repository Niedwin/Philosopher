/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 00:55:46 by guviure           #+#    #+#             */
/*   Updated: 2025/08/28 05:29:05 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long long	current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000LL + tv.tv_usec / 1000);
}

void	precise_sleep(long long ms)
{
	long long	start;

	start = current_time_ms();
	while (current_time_ms() - start < ms)
		usleep(100);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

void	print_status(t_philo *philo, char *action)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (!check_stop(philo->data))
		printf("%lld %d %s\n", current_time_ms() - philo->data->start_time,
			philo->id, action);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
