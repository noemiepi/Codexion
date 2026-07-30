/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_edf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:28:05 by npillet           #+#    #+#             */
/*   Updated: 2026/07/30 10:01:38 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	*insert_new_node(t_heap *heap, int burnout);
static void	insert(t_heap *heap);
static void	delete_node(t_heap *heap);
static void	check_deadline(t_heap *heap, int i);

void	scheduler_edf(t_heap *heap, t_coder *coder, int step)
{
	pthread_mutex_lock(&heap->mutex_heap);
	if (step == ADD)
		insert_new_node(heap, coder->burnout_time);
	if (step == REMOVE)
		delete_node(heap);
	pthread_mutex_unlock(&heap->mutex_heap);
}

static void	*insert_new_node(t_heap *heap, int burnout)
{
	t_edf	*node;

	node = malloc(sizeof(t_edf));
	if (node == NULL)
		return (NULL);
	node->deadline = burnout;
	node->left = NULL;
	node->right = NULL;
	heap->size += 1;
	insert(heap);
	return (NULL);
}

static void	insert(t_heap *heap)
{
	t_edf	tmp;
	int		parent_node;
	int		i;

	parent_node = heap->size / 2;
	i = heap->size;
	while (i > 0 && heap->node[i].deadline < heap->node[parent_node].deadline)
	{
		tmp = heap->node[i];
		heap->node[i] = heap->node[parent_node];
		heap->node[parent_node] = tmp;
		i = i / 2;
		parent_node = parent_node / 2;
	}
}

static void	delete_node(t_heap *heap)
{
	t_edf	tmp;
	int		child_node;
	int		i;

	i = 1;
	child_node = 2;
	heap->node[1] = heap->node[heap->size];
	heap->size--;
	while (i > 0)
	{
		if (child_node + 1 <= heap->size)
			child_node++;
		if (heap->node[i].deadline >= heap->node[child_node].deadline)
		{
			tmp = heap->node[i];
			heap->node[i] = heap->node[child_node];
			heap->node[child_node] = tmp;
		}
		i = child_node;
		child_node = child_node * 2;
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
		}
		else
			break ;
	}
}
