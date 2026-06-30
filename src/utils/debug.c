/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 14:45:18 by npillet           #+#    #+#             */
/*   Updated: 2026/06/30 15:53:59 by npillet          ###   ########.fr       */
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

void	debug_print_queue(t_queue *manager)
{
	int		count;
	t_fifo	*current;

	count = 0;
	current = manager->front;
	while (current != NULL)
	{
		printf("[Queue %d] Coder %d\n", count, current->data->id);
		count++;
		current = current->next;
	}
}
