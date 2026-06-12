/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 11:21:45 by npillet           #+#    #+#             */
/*   Updated: 2026/06/12 17:21:24 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	parsing(int argc, char **argv)
{
	if (args_parsing(argc, argv))
		return (1);
	else
	{
		if (time_parsing(argv))
			return (1);
	}
	return (0);
}

int	args_parsing(int argc, char **argv)
{
	if (check_number_of_arguments(argc))
	{
		printf("Invalid number of provided arguments (%d),"
			"there should be 8.\n", argc - 1);
		return (1);
	}
	if (check_number_of_coder(argv[1]))
	{
		printf("Invalid number of coders (%s is outside the limits)."
			"\n", argv[1]);
		return (1);
	}
	if (check_number_of_compiles(argv[6]))
	{
		printf("Invalid number of required compiles (%s is outside "
			"the limits).\n", argv[6]);
		return (1);
	}
	if (check_scheduler(argv[8]))
	{
		printf("Invalid scheduler, choose between fifo or edf.\n");
		return (1);
	}
	return (0);
}

int	time_parsing(char **argv)
{
	int	i;

	i = 2;
	while (i <= 7)
	{
		if (check_given_time(argv[i]))
		{
			printf("Invalid time input (%s).\n", argv[i]);
			return (1);
		}
		if (i == 5)
			i = 6;
		i += 1;
	}
	return (0);
}
