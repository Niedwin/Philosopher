/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:55:52 by guviure           #+#    #+#             */
/*   Updated: 2025/08/22 23:58:41 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void set_someone_is_dead(t_data *data, int value)
{
    pthread_mutex_lock(&data->death_mutex);
    data->someone_is_dead = value;
    pthread_mutex_unlock(&data->death_mutex);
}

int get_someone_is_dead(t_data *data)
{
    int value;
    pthread_mutex_lock(&data->death_mutex);
    value = data->someone_is_dead;
    pthread_mutex_unlock(&data->death_mutex);
    return (value);
}

void increment_meals_eaten(t_philo *philo)
{
    pthread_mutex_lock(&philo->meal_mutex);
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->meal_mutex);
}

int get_meals_eaten(t_philo *philo)
{
    int meals;
    pthread_mutex_lock(&philo->meal_mutex);
    meals = philo->meals_eaten;
    pthread_mutex_unlock(&philo->meal_mutex);
    return (meals);
}

void set_last_meal(t_philo *philo, long time)
{
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal = time;
    pthread_mutex_unlock(&philo->meal_mutex);
}
