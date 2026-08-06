/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:42:09 by npillet           #+#    #+#             */
/*   Updated: 2026/08/06 14:51:17 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static bool	in_heap(t_heap *heap, t_coder *coder);
static bool	beats(t_coder *coder1, t_coder *coder2);
static bool	protected_heap(t_heap *heap, t_coder *coder, \
	t_coder *left, t_coder *right);

int	is_priority(t_heap *heap, t_data *data, t_coder *coder)
{
	t_coder	*left;
	t_coder	*right;
	bool	result;

	if (data->nb_coders <= 1)
		return (true);
	left = &data->coder[(coder->id - 1 + data->nb_coders) % data->nb_coders];
	right = &data->coder[(coder->id + 1) % data->nb_coders];
	pthread_mutex_lock(&heap->mutex_heap);
	result = protected_heap(heap, coder, left, right);
	pthread_mutex_unlock(&heap->mutex_heap);
	return (result);
}

static bool	protected_heap(t_heap *heap, t_coder *coder, \
	t_coder *left, t_coder *right)
{
	bool	result;

	result = true;
	if (result && in_heap(heap, left))
	{
		pthread_mutex_lock(&coder->mutex_burnout);
		pthread_mutex_lock(&left->mutex_burnout);
		if (beats(coder, left) == false)
			result = false;
		pthread_mutex_unlock(&coder->mutex_burnout);
		pthread_mutex_unlock(&left->mutex_burnout);
	}
	if (result && right != left && in_heap(heap, right))
	{
		pthread_mutex_lock(&coder->mutex_burnout);
		pthread_mutex_lock(&right->mutex_burnout);
		if (beats(coder, right) == false)
			result = false;
		pthread_mutex_unlock(&coder->mutex_burnout);
		pthread_mutex_unlock(&right->mutex_burnout);
	}
	return (result);
}

static bool	in_heap(t_heap *heap, t_coder *coder)
{
	int	i;

	i = 0;
	while (i < heap->size)
	{
		if (heap->node[i].coder == coder)
			return (true);
		i++;
	}
	return (false);
}

static bool	beats(t_coder *coder1, t_coder *coder2)
{
	if (coder1->burnout_time != coder2->burnout_time)
		return (coder1->burnout_time < coder2->burnout_time);
	return (coder1->id < coder2->id);
}
