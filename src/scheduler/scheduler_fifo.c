/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_fifo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:47:24 by npillet           #+#    #+#             */
/*   Updated: 2026/09/02 10:29:09 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void		*insert_new_node(t_queue *queue, t_coder *coder);
static void		*delete_node(t_queue *queue);

void	scheduler_fifo(t_queue *queue, t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	pthread_mutex_lock(&queue->mutex_queue);
	insert_new_node(queue, coder);
	while (get_active_sim(data)
		&& (data->queue->front->coder != coder || take_dongle(data, coder)))
	{
		if (get_active_sim(data) && queue->front->coder == coder)
		{
			pthread_mutex_unlock(&data->queue->mutex_queue);
			usleep(1000);
			pthread_mutex_lock(&data->queue->mutex_queue);
		}
		else
			pthread_cond_wait(&data->queue->cond_queue,
				&data->queue->mutex_queue);
	}
	if (get_active_sim(data))
	{
		delete_node(queue);
		pthread_cond_broadcast(&data->queue->cond_queue);
	}
	pthread_mutex_unlock(&queue->mutex_queue);
}

static void	*insert_new_node(t_queue *queue, t_coder *coder)
{
	t_fifo	*node;

	node = malloc(sizeof(t_fifo));
	if (node == NULL)
		return (NULL);
	node->coder = coder;
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
