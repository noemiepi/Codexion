/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:44:05 by npillet           #+#    #+#             */
/*   Updated: 2026/09/01 13:16:51 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

bool	check_number_of_arguments(int nb)
{
	if (nb == 9)
		return (true);
	return (false);
}

bool	check_number_of_coder(char *coder, t_data *data)
{
	int	nb_coder;

	nb_coder = ft_atoi(coder);
	if (nb_coder >= 1 && nb_coder <= MAX_CODERS)
	{
		data->nb_coders = nb_coder;
		return (true);
	}
	return (false);
}

bool	check_given_time(char *given_time)
{
	int	time;

	time = ft_atoi(given_time);
	if (time >= 0)
		return (true);
	return (false);
}

bool	check_number_of_compiles(char *compiles, t_data *data)
{
	int	nb_compiles;

	nb_compiles = ft_atoi(compiles);
	if (nb_compiles >= 0)
	{
		data->nb_compiles_req = nb_compiles;
		return (true);
	}
	return (false);
}

bool	check_scheduler(char *schedule, t_data *data)
{
	int	i;
	int	j;

	i = strcmp(schedule, FIFO);
	j = strcmp(schedule, EDF);
	if (i == 0 || j == 0)
	{
		data->scheduler = schedule;
		return (true);
	}
	return (false);
}
