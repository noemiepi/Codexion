/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_edf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:28:05 by npillet           #+#    #+#             */
/*   Updated: 2026/08/04 08:28:32 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	*insert_new_node(t_heap *heap, t_coder *coder, int burnout);
static void	delete_node(t_heap *heap, t_coder *coder);
static void	check_deadline(t_heap *heap, int i);
static int	is_priority(t_heap *heap, t_coder *coder);

void	scheduler_edf(t_heap *heap, t_coder *coder)
{
	pthread_mutex_lock(&heap->mutex_heap);
	insert_new_node(heap, coder, coder->burnout_time);
	pthread_cond_broadcast(&heap->cond_heap);
	pthread_mutex_unlock(&heap->mutex_heap);
	while (get_active_sim(coder->data))
	{
		if (is_priority(heap, coder))
		{
			if (take_dongle(coder) == false)
				break ;
		}
		usleep(1000);
	}
	pthread_mutex_lock(&heap->mutex_heap);
	delete_node(heap, coder);
	pthread_cond_broadcast(&heap->cond_heap);
	pthread_mutex_unlock(&heap->mutex_heap);
}

static void	*insert_new_node(t_heap *heap, t_coder *coder, int burnout)
{
	t_edf	*node;
	t_edf	tmp;
	int		i;

	node = malloc(sizeof(t_edf));
	if (node == NULL)
		return (NULL);
	node->coder = coder;
	node->deadline = burnout;
	heap->node[heap->size] = *node;
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

	while ((i * 2) + 1 <= heap->size)
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

static int	is_priority(t_heap *heap, t_coder *coder)
{
	long long	time;
	int			left;
	int			right;

	time = coder->burnout_time;
	left = (coder->id - 1 + coder->data->nb_coders) % coder->data->nb_coders;
	right = (coder->id + 1) % coder->data->nb_coders;
	if (heap->node[left].deadline < time)
		return (false);
	if (heap->node[right].deadline < time)
		return (false);
	return (true);
}
