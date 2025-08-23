/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guviure <guviure@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:02:38 by guviure           #+#    #+#             */
/*   Updated: 2025/08/23 01:34:44 by guviure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	parse_args(int argc, char *argv[], t_data *data)
{
	if (argc != 5 && argc != 6)
		return (0);
	data->number_of_philosopher = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->number_of_meals = -1;
	if (argc == 6)
		data->number_of_meals = ft_atoi(argv[5]);
	data->someone_is_dead = 0;
	data->start_time = get_time();
	return (1);
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
