/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_edf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:28:05 by npillet           #+#    #+#             */
/*   Updated: 2026/08/06 14:42:28 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	*insert_new_node(t_heap *heap, t_coder *coder, long long burnout);
static void	delete_node(t_heap *heap, t_coder *coder);
static void	check_deadline(t_heap *heap, int i);

void	scheduler_edf(t_heap *heap, t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	pthread_mutex_lock(&heap->mutex_heap);
	insert_new_node(heap, coder, coder->burnout_time);
	pthread_cond_broadcast(&heap->cond_heap);
	pthread_mutex_unlock(&heap->mutex_heap);
	while (get_active_sim(coder->data))
	{
		if (is_priority(heap, data, coder))
		{
			if (take_dongle(data, coder) == false)
				break ;
		}
		usleep(1000);
	}
	pthread_mutex_lock(&heap->mutex_heap);
	delete_node(heap, coder);
	pthread_cond_broadcast(&heap->cond_heap);
	pthread_mutex_unlock(&heap->mutex_heap);
}

static void	*insert_new_node(t_heap *heap, t_coder *coder, long long burnout)
{
	t_edf	tmp;
	int		i;

	heap->node[heap->size].coder = coder;
	heap->node[heap->size].deadline = burnout;
	heap->size += 1;
	i = heap->size - 1;
	while (i > 0 && heap->node[i].deadline < heap->node[(i - 1) / 2].deadline)
	{
		tmp = heap->node[i];
		heap->node[i] = heap->node[(i - 1) / 2];
		heap->node[(i - 1) / 2] = tmp;
		i = (i - 1) / 2;
	}
	return (NULL);
}

static void	delete_node(t_heap *heap, t_coder *coder)
{
	t_edf	tmp;
	int		i;

	i = 0;
	while (i < heap->size)
	{
		if (heap->node[i].coder == coder)
			break ;
		i++;
	}
	if (i == heap->size)
		return ;
	heap->size--;
	heap->node[i] = heap->node[heap->size];
	while (i > 0 && heap->node[i].deadline < heap->node[(i - 1) / 2].deadline)
	{
		tmp = heap->node[i];
		heap->node[i] = heap->node[(i - 1) / 2];
		heap->node[(i - 1) / 2] = tmp;
		i = (i - 1) / 2;
	}
	check_deadline(heap, i);
}

static void	check_deadline(t_heap *heap, int i)
{
	t_edf	tmp;
	int		left;
	int		right;
	int		smallest;

	while ((i * 2) + 1 < heap->size)
	{
		left = (i * 2) + 1;
		right = (i * 2) + 2;
		smallest = left;
		if (right < heap->size && \
			(heap->node[right].deadline < heap->node[left].deadline))
			smallest = right;
		if (heap->node[smallest].deadline < heap->node[i].deadline)
		{
			tmp = heap->node[i];
			heap->node[i] = heap->node[smallest];
			heap->node[smallest] = tmp;
			i = smallest;
		}
		else
			break ;
	}
}
