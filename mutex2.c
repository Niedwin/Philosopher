/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 17:55:52 by guviure           #+#    #+#             */
/*   Updated: 2025/08/22 23:58:41 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long get_last_meal(t_philo *philo)
{
    long time;
    pthread_mutex_lock(&philo->meal_mutex);
    time = philo->last_meal;
    pthread_mutex_unlock(&philo->meal_mutex);
    return (time);
}
