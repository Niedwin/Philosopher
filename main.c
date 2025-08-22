/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:02:38 by guviure           #+#    #+#             */
/*   Updated: 2025/08/23 00:03:17 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	parse_args(int argc, char *argv[], t_data *data)
{
	if (argc != 5 && argc != 6)
		return (0);
	data->number_of_philosopher = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data-> time_to_sleep = ft_atoi(argv[4]);
	data->number_of_meals = -1;
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	data->someone_is_dead = 0;
	data->start_time = get_time();
	return (1);
}
void	print_message(t_philo * philo, char	*msg)
{
	long	time;
	
	pthread_mutex_lock(&philo->data->print_mutex);
	time = get_time() - philo->data->start_time;
	if (!philo->data->someone_is_dead)
		printf("%ld %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
}
void	smart_sleep(long time_ms, t_data *data)
{
	long	start_time;
	long	elapsed_time;

	start_time = get_time();
	while  (1)
	{
		elapsed_time = get_time() - start_time;
		if (elapsed_time >= time_ms)
			break;
		if (data->someone_is_dead)
			break;
		usleep(100);
	}
}

void	*ft_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;

	while (!philo->data->someone_is_dead)
	{
		print_message(philo, "is thinking");
		pthread_mutex_lock(philo->left_fork);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_message(philo, "has taken a fork");
		print_message(philo, "is eating");
		philo->last_meal = get_time();
		smart_sleep(philo->data->time_to_eat, philo->data);
		philo->meals_eaten++;
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		print_message(philo, "is sleeping");
		smart_sleep(philo->data->time_to_sleep, philo->data);
	}
	return (NULL);
}

void	*monitor_routine(void *arg)
{
	t_data *data;
	int	i;
	
	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->number_of_philosopher)
		{
			if (get_time() - data->philo[i].last_meal > data->time_to_die)
			{
				print_message(&data->philo[i], "died");
				data->someone_is_dead = 1;
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
}

void	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < data->number_of_philosopher)
	{
		data->philo[i].last_meal = get_time();
		pthread_create(&data->philo[i].thread, NULL, ft_routine, &data->philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, monitor_routine, data);
	i = 0;
	while (i < data->number_of_philosopher)
		pthread_join(data->philo[i].thread, NULL);
	pthread_join(monitor, NULL);
}

void	end_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i< data->number_of_philosopher)
		pthread_mutex_destroy(&data->forks[i++]);
	pthread_mutex_destroy(&data->print_mutex);
	free(data->forks);
	free(data->philo);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	if (!parse_args(argc, argv, &data))
		return (1);
	if (!init_all(&data))
		return (1);
	start_simulation(&data);
	end_simulation(&data);
	return (0);
}