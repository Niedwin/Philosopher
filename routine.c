/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 01:09:53 by guviure           #+#    #+#             */
/*   Updated: 2025/08/23 01:58:24 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	set_last_meal(philo, get_time());
	smart_sleep(philo->data->time_to_eat, philo->data);
	increment_meals_eaten(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

static void	philo_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	smart_sleep(philo->data->time_to_sleep, philo->data);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		current_meals;

	philo = (t_philo *)arg;
	while (!get_someone_is_dead(philo->data))
	{
		current_meals = get_meals_eaten(philo);
		if (philo->data->number_of_meals != -1
			&& get_meals_eaten(philo) >= philo->data->number_of_meals)
			break ;
		print_message(philo, "is thinking");
		philo_eat(philo);
		current_meals = get_meals_eaten(philo);
		if (philo->data->number_of_meals == -1
			|| current_meals < philo->data->number_of_meals)
			philo_sleep(philo);
	}
	return (NULL);
}
