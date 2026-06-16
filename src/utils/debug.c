/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 14:45:18 by npillet           #+#    #+#             */
/*   Updated: 2026/06/16 15:16:55 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	debug_print_struct(t_data *data)
{
	int	i;

	i = 0;
	while (data->nb_coders != i)
	{
		printf("Coder %d\n", data->coder[i].id);
		i++;
	}
	i = 0;
	while (data->nb_coders != i)
	{
		printf("Dongle %d\n", data->dongle[i].id);
		i++;
	}
}
