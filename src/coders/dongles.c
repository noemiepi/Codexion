/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:50:53 by npillet           #+#    #+#             */
/*   Updated: 2026/09/02 11:08:21 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static bool	taking_dongle(t_coder *coder, t_dongle *first, t_dongle *second);
static bool	try_take_dongle(t_dongle *dongle, t_data *data);
static void	cond_thread(t_data *data);

bool	take_dongle(t_data *data, t_coder *coder)
{
	t_dongle	*first;
	t_dongle	*second;

	first = NULL;
	second = NULL;
	if (data->nb_coders > 1 && coder->id == data->nb_coders - 1)
	{
		first = coder->right_dongle;
		second = coder->left_dongle;
	}
	else
	{
		first = coder->left_dongle;
		second = coder->right_dongle;
	}
	return (taking_dongle(coder, first, second));
}

bool	taking_dongle(t_coder *coder, t_dongle *first, t_dongle *second)
{
	if (try_take_dongle(first, coder->data) == true)
	{
		if (second == NULL)
		{
			pthread_mutex_unlock(&first->mutex_dongle);
			return (true);
		}
		if (try_take_dongle(second, coder->data) == true)
		{
			coder->has_dongle = true;
			return (false);
		}
		pthread_mutex_unlock(&first->mutex_dongle);
		return (true);
	}
	return (true);
}

static bool	try_take_dongle(t_dongle *dongle, t_data *data)
{
	pthread_mutex_lock(&dongle->mutex_dongle);
	if (get_current_time(data) >= dongle->cooldown)
		return (true);
	pthread_mutex_unlock(&dongle->mutex_dongle);
	return (false);
}

void	release_dongle(t_data *data, t_coder *coder)
{
	long long	curr_time;

	if (coder->has_dongle == false)
		return ;
	curr_time = get_current_time(data);
	if (coder->left_dongle != NULL)
	{
		coder->left_dongle->cooldown = curr_time + data->dongle_cooldown;
		pthread_mutex_unlock(&coder->left_dongle->mutex_dongle);
	}
	if (coder->right_dongle != NULL)
	{
		coder->right_dongle->cooldown = curr_time + data->dongle_cooldown;
		pthread_mutex_unlock(&coder->right_dongle->mutex_dongle);
	}
	coder->has_dongle = false;
	cond_thread(data);
}

static void	cond_thread(t_data *data)
{
	if (strcmp(FIFO, data->scheduler) == 0)
	{
		pthread_mutex_lock(&data->queue->mutex_queue);
		pthread_cond_broadcast(&data->queue->cond_queue);
		pthread_mutex_unlock(&data->queue->mutex_queue);
	}
	else
	{
		pthread_mutex_lock(&data->heap->mutex_heap);
		pthread_cond_broadcast(&data->heap->cond_heap);
		pthread_mutex_unlock(&data->heap->mutex_heap);
	}
}
