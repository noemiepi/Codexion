/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:56:04 by npillet           #+#    #+#             */
/*   Updated: 2026/06/30 12:04:42 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	create_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->mutex_print, NULL);
	pthread_mutex_init(&data->queue->mutex_queue, NULL);
	while (data->nb_coders != i)
	{
		pthread_mutex_init(&data->dongle[i].mutex_dongle, NULL);
		i++;
	}
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->mutex_print);
	pthread_mutex_destroy(&data->queue->mutex_queue);
	while (data->nb_coders != i)
	{
		pthread_mutex_destroy(&data->dongle[i].mutex_dongle);
		i++;
	}
}
