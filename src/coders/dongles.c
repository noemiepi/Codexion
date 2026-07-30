/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:50:53 by npillet           #+#    #+#             */
/*   Updated: 2026/07/30 10:39:04 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	cond_release(t_data *data);

bool	take_dongle(t_coder *coder)
{
	if (try_take_dongle(coder->left_dongle, coder->data) == true)
	{
		if (coder->right_dongle == NULL)
		{
			pthread_mutex_unlock(&coder->left_dongle->mutex_dongle);
			return (true);
		}
		if (try_take_dongle(coder->right_dongle, coder->data) == true)
		{
			printf(DONGLE_TAKEN, get_current_time(coder->data), coder->id);
			printf(DONGLE_TAKEN, get_current_time(coder->data), coder->id);
			return (false);
		}
		else
		{
			pthread_mutex_unlock(&coder->left_dongle->mutex_dongle);
			return (true);
		}
	}
	return (true);
}

bool	try_take_dongle(t_dongle *dongle, t_data *data)
{
	if (get_current_time(data) >= dongle->cooldown)
	{
		pthread_mutex_lock(&dongle->mutex_dongle);
		return (true);
	}
	return (false);
}

void	release_dongle(t_coder *coder)
{
	long long	curr_time;
	t_data		*data;

	data = coder->data;
	curr_time = get_current_time(coder->data);
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
	cond_release(data);
}

static void	cond_release(t_data *data)
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
