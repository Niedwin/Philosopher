/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 01:07:01 by guviure           #+#    #+#             */
/*   Updated: 2025/08/28 05:09:22 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	take_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->data->number_of_philosophers;
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->data->forks[right]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[left]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right]);
		print_status(philo, "has taken a fork");
	}
}

void	release_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;
	right = philo->id % philo->data->number_of_philosophers;
	pthread_mutex_unlock(&philo->data->forks[left]);
	pthread_mutex_unlock(&philo->data->forks[right]);
}

static void	check_all_done(t_data *data)
{
	int	i;
	int	all_done;

	all_done = 1;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_lock(&data->philo[i].meal_mutex);
		if (data->philo[i].meals_eaten
			< data->number_of_times_each_philosopher_must_eat)
			all_done = 0;
		pthread_mutex_unlock(&data->philo[i].meal_mutex);
		i++;
	}
	if (all_done)
		set_stop(data);
}

void	philo_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	take_forks(philo);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = current_time_ms();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	precise_sleep(data->time_to_eat);
	release_forks(philo);
	if (data->number_of_times_each_philosopher_must_eat > 0)
		check_all_done(data);
}
