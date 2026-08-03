/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:50:53 by npillet           #+#    #+#             */
/*   Updated: 2026/08/03 14:12:46 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

bool	take_dongle(t_coder *coder)
{
	t_data	*data;

	data = coder->data;
	if (try_take_dongle(coder->left_dongle, coder->data) == true)
	{
		if (coder->right_dongle == NULL)
		{
			pthread_mutex_unlock(&coder->left_dongle->mutex_dongle);
			return (true);
		}
		if (try_take_dongle(coder->right_dongle, coder->data) == true)
			return (false);
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
	pthread_mutex_lock(&dongle->mutex_dongle);
	if (get_current_time(data) >= dongle->cooldown)
		return (true);
	pthread_mutex_unlock(&dongle->mutex_dongle);
	return (false);
}

void	release_dongle(t_data *data, t_coder *coder)
{
	long long	curr_time;

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
