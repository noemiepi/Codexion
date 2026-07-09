/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:18:04 by npillet           #+#    #+#             */
/*   Updated: 2026/07/09 14:43:46 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	free_structures(t_data *data)
{
	t_fifo	*node;
	t_fifo	*tmp;

	free(data->dongle);
	free(data->coder);
	node = data->queue->front;
	while (node != NULL)
	{
		tmp = node->next;
		free(node);
		node = tmp;
	}
	free(data->queue);
}
