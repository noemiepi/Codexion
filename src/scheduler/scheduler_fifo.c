/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_fifo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:47:24 by npillet           #+#    #+#             */
/*   Updated: 2026/07/09 21:33:00 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void		*insert_new_node(t_queue *queue, t_coder *coder);
static void		*delete_node(t_queue *queue);

void	scheduler_fifo(t_queue *queue, t_coder *coder, int step)
{
	pthread_mutex_lock(&queue->mutex_queue);
	if (step == ADD)
		insert_new_node(queue, coder);
	if (step == REMOVE)
		delete_node(queue);
	pthread_mutex_unlock(&queue->mutex_queue);
}

static void	*insert_new_node(t_queue *queue, t_coder *coder)
{
	t_fifo	*node;

	node = malloc(sizeof(t_fifo));
	if (node == NULL)
		return (NULL);
	node->data = coder;
	node->next = NULL;
	if (queue->front == NULL)
	{
		queue->front = node;
		queue->rear = node;
	}
	else
	{
		queue->rear->next = node;
		queue->rear = node;
	}
	return (NULL);
}

static void	*delete_node(t_queue *queue)
{
	t_fifo	*node;

	if (queue->front == NULL)
		return (NULL);
	node = queue->front;
	queue->front = node->next;
	if (queue->front == NULL)
		queue->rear = NULL;
	free(node);
	return (NULL);
}
