/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:56:04 by npillet           #+#    #+#             */
/*   Updated: 2026/09/02 10:11:08 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	create_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->mutex_sim, NULL);
	pthread_mutex_init(&data->queue->mutex_queue, NULL);
	pthread_mutex_init(&data->heap->mutex_heap, NULL);
	pthread_cond_init(&data->queue->cond_queue, NULL);
	pthread_cond_init(&data->heap->cond_heap, NULL);
	while (data->nb_coders != i)
	{
		pthread_mutex_init(&data->coder[i].mutex_burnout, NULL);
		pthread_mutex_init(&data->dongle[i].mutex_dongle, NULL);
		i++;
	}
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_sim);
	pthread_mutex_destroy(&data->queue->mutex_queue);
	pthread_mutex_destroy(&data->heap->mutex_heap);
	pthread_cond_destroy(&data->queue->cond_queue);
	pthread_cond_destroy(&data->heap->cond_heap);
	while (data->nb_coders != i)
	{
		pthread_mutex_destroy(&data->coder[i].mutex_burnout);
		pthread_mutex_destroy(&data->dongle[i].mutex_dongle);
		i++;
	}
}
