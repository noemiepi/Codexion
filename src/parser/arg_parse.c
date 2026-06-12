/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:44:05 by npillet           #+#    #+#             */
/*   Updated: 2026/06/12 16:57:32 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

int	check_number_of_arguments(int nb)
{
	if (nb == 9)
		return (0);
	return (1);
}

int	check_number_of_coder(char *coder)
{
	int	nb_coder;

	nb_coder = ft_atoi(coder);
	if (nb_coder >= 1 && nb_coder <= MAX_CODER)
		return (0);
	return (1);
}

int	check_given_time(char *given_time)
{
	int	time;

	time = ft_atoi(given_time);
	if (time >= 0)
		return (0);
	return (1);
}

int	check_number_of_compiles(char *compiles)
{
	int	nb_compiles;

	nb_compiles = ft_atoi(compiles);
	if (nb_compiles >= 0)
		return (0);
	return (1);
}

int	check_scheduler(char *schedule)
{
	int	i;
	int	j;

	i = strcmp(schedule, "fifo");
	j = strcmp(schedule, "edf");
	if (i == 0 || j == 0)
		return (0);
	return (1);
}
