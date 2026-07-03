/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_edf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:28:05 by npillet           #+#    #+#             */
/*   Updated: 2026/07/03 16:07:36 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static t_edf	*insert_new_node(int burnout);
static t_edf	*insert(t_edf *node, int burnout);
// static t_coder	*delete_node(t_queue *queue);

void	scheduler_edf(t_heap *heap, t_coder *coder, int step)
{
	pthread_mutex_lock(&heap->mutex_heap);
	if (step == ADD)
		insert_new_node(coder->burnout_time);
	if (step == REMOVE)
		printf("remove");
		// delete_node(heap);
	pthread_mutex_unlock(&heap->mutex_heap);
}

static t_edf	*insert_new_node(int burnout)
{
	t_edf	*node;

	node = malloc(sizeof(t_edf));
	if (node == NULL)
		return (NULL);
	node->data = burnout;
	node->left = NULL;
	node->right = NULL;
	insert(node, burnout);
	return (node);
}

static t_edf	*insert(t_edf *node, int burnout)
{
	if (node == NULL)
		return (insert_new_node(burnout));
	if (burnout < node->data)
		node->left = insert(node->left, burnout);
	else if (burnout > node->data)
		node->left = insert(node->right, burnout);
	return (node);
}

// static t_coder	*delete_node(t_heap *heap)
// {
// 	;
// }
