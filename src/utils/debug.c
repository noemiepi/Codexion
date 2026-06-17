/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 14:45:18 by npillet           #+#    #+#             */
/*   Updated: 2026/06/17 15:50:51 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	debug_print_struct(t_data *data)
{
	int	i;

	i = 0;
	while (data->nb_coders != i)
	{
		printf("\nCoder %d:\n", data->coder[i].id);
		printf("- Thread: %lu\n", data->coder[i].thread_id);
		printf("- Left dongle: %p\n", data->coder[i].left_dongle);
		printf("- Right dongle: %p\n", data->coder[i].right_dongle);
		i++;
	}
}
