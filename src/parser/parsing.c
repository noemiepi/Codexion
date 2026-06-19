/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 11:21:45 by npillet           #+#    #+#             */
/*   Updated: 2026/06/19 19:10:28 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static bool	args_parsing(int argc, char **argv, t_data *data);
static bool	time_parsing(char **argv, t_data *data);

bool	parsing(int argc, char **argv, t_data *data)
{
	if (!(args_parsing(argc, argv, data)))
		return (false);
	else
	{
		if (!(time_parsing(argv, data)))
			return (false);
	}
	return (true);
}

static bool	args_parsing(int argc, char **argv, t_data *data)
{
	if (!(check_number_of_arguments(argc)))
	{
		printf("Invalid number of provided arguments (%d),"
			"there should be 8.\n", argc - 1);
		return (false);
	}
	if (!(check_number_of_coder(argv[1], data)))
	{
		printf("Invalid number of coders (%s is outside the limits)."
			"\n", argv[1]);
		return (false);
	}
	if (!(check_number_of_compiles(argv[6], data)))
	{
		printf("Invalid number of required compiles (%s is outside "
			"the limits).\n", argv[6]);
		return (false);
	}
	if (!(check_scheduler(argv[8], data)))
	{
		printf("Invalid scheduler, choose between fifo or edf.\n");
		return (false);
	}
	return (true);
}

static bool	time_parsing(char **argv, t_data *data)
{
	int		time;
	int		i;

	i = 2;
	while (i <= 7)
	{
		if (!(check_given_time(argv[i])))
		{
			printf("Invalid time input (%d).\n", time);
			return (false);
		}
		time = ft_atoi(argv[i]);
		if (i == 2)
			data->time_burnout = time;
		if (i == 3)
			data->time_compile = time;
		if (i == 4)
			data->time_debug = time;
		if (i == 5)
			data->time_refactor = time;
		if (i == 7)
			data->dongle_cooldown = time;
		i += 1;
	}
	return (true);
}
