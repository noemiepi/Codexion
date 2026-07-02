/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:36:10 by npillet           #+#    #+#             */
/*   Updated: 2026/07/02 10:48:22 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*coders_action(void *arg)
{
	t_coder	*coder;
	t_data	*data;

	coder = (t_coder *)arg;
	data = coder->data;
	while (coder->finish == false && get_active_sim(data))
	{
		if (strcmp(FIFO, data->scheduler) == 0)
			scheduler_fifo(data->queue, coder, ADD);
		pthread_mutex_lock(&data->mutex_print);
		terminal_logs(data, coder);
		pthread_mutex_unlock(&data->mutex_print);
	}
	return (NULL);
}

void	terminal_logs(t_data *data, t_coder *coder)
{
	if (get_active_sim(data))
	{
		take_dongle(coder);
		printf(COMPILING, get_current_time(data), coder->id);
		coder->burnout_time = get_current_time(data);
		coder->nb_compile += 1;
		if (coder->nb_compile == data->nb_compiles_req)
			coder->finish = true;
		if (strcmp(FIFO, data->scheduler) == 0)
			scheduler_fifo(data->queue, coder, REMOVE);
		release_dongle(coder);
		usleep(data->time_compile * 1000);
	}
	if (get_active_sim(data))
	{
		printf(DEBUGGING, get_current_time(data), coder->id);
		usleep(data->time_debug * 1000);
	}
	if (get_active_sim(data))
	{
		printf(REFACTORING, get_current_time(data), coder->id);
		usleep(data->time_refactor * 1000);
	}
}
