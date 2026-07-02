/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:56:04 by npillet           #+#    #+#             */
/*   Updated: 2026/07/02 11:39:12 by npillet          ###   ########.fr       */
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
	while (data->nb_coders != i)
	{
		pthread_mutex_init(&data->dongle[i].mutex_dongle, NULL);
		i++;
	}
	pthread_cond_init(&data->cond, NULL);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->mutex_sim);
	pthread_mutex_destroy(&data->queue->mutex_queue);
	while (data->nb_coders != i)
	{
		pthread_mutex_destroy(&data->dongle[i].mutex_dongle);
		i++;
	}
	pthread_cond_destroy(&data->cond);
}
