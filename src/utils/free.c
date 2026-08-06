/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:18:04 by npillet           #+#    #+#             */
/*   Updated: 2026/08/06 12:11:45 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	free_memory_fifo(t_data *data);

void	free_structures(t_data *data)
{
	free_memory_fifo(data);
	free(data->heap->node);
	free(data->queue);
	free(data->heap);
}

static void	free_memory_fifo(t_data *data)
{
	t_fifo	*curr;
	t_fifo	*next;

	curr = data->queue->front;
	if (data->coder != NULL)
		free(data->coder);
	if (data->dongle != NULL)
		free(data->dongle);
	while (curr != NULL)
	{
		next = curr->next;
		free(curr);
		curr = next;
	}
}
