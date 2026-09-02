/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:36:10 by npillet           #+#    #+#             */
/*   Updated: 2026/09/02 15:54:06 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	terminal_logs1(t_data *data, t_coder *coder);
static void	terminal_logs2(t_data *data, t_coder *coder);

void	*coders_action(void *arg)
{
	t_coder	*coder;
	t_data	*data;

	coder = (t_coder *)arg;
	data = coder->data;
	while (coder->finish == false && get_active_sim(data))
	{
		if (strcmp(FIFO, data->scheduler) == 0)
			scheduler_fifo(data->queue, coder);
		else if (strcmp(EDF, data->scheduler) == 0)
			scheduler_edf(data->heap, coder);
		terminal_logs1(data, coder);
		terminal_logs2(data, coder);
	}
	return (NULL);
}

static void	terminal_logs1(t_data *data, t_coder *coder)
{
	if (get_active_sim(data) == false)
	{
		release_dongle(data, coder);
		return ;
	}
	pthread_mutex_lock(&data->mutex_print);
	printf(DONGLE_TAKEN, get_current_time(coder->data), coder->id);
	printf(DONGLE_TAKEN, get_current_time(coder->data), coder->id);
	printf(COMPILING, get_current_time(data), coder->id);
	pthread_mutex_unlock(&data->mutex_print);
	pthread_mutex_lock(&coder->mutex_burnout);
	coder->burnout_time = get_current_time(data);
	coder->nb_compile += 1;
	if (coder->nb_compile == data->nb_compiles_req)
		coder->finish = true;
	pthread_mutex_unlock(&coder->mutex_burnout);
}

static void	terminal_logs2(t_data *data, t_coder *coder)
{
	usleep(data->time_compile * 1000);
	release_dongle(data, coder);
	if (get_active_sim(data) == false)
		return ;
	pthread_mutex_lock(&data->mutex_print);
	printf(DEBUGGING, get_current_time(data), coder->id);
	pthread_mutex_unlock(&data->mutex_print);
	usleep(data->time_debug * 1000);
	if (get_active_sim(data) == false)
		return ;
	pthread_mutex_lock(&data->mutex_print);
	printf(REFACTORING, get_current_time(data), coder->id);
	pthread_mutex_unlock(&data->mutex_print);
	usleep(data->time_refactor * 1000);
}
