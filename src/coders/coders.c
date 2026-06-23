/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:36:10 by npillet           #+#    #+#             */
/*   Updated: 2026/06/23 18:40:47 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*coders_action(void *arg)
{
	t_coder	*coder;
	t_data	*data;
	
	coder = (t_coder *)arg;
	data = coder->data;
	pthread_mutex_lock(&data->mutex_print);
	take_dongle(data, coder);
	terminal_logs(data, coder);
	pthread_mutex_unlock(&data->mutex_print);
	return (NULL);
}

void	take_dongle(t_data *data, t_coder *coder)
{	
	printf(DONGLE_TAKEN, get_current_time(data), coder->id);
}

void	terminal_logs(t_data *data, t_coder *coder)
{
	printf(COMPILING, get_current_time(data), coder->id);
	usleep(data->time_compile * 1000);
	printf(DEBUGGING, get_current_time(data), coder->id);
	usleep(data->time_debug * 1000);
	printf(REFACTORING, get_current_time(data), coder->id);
	usleep(data->time_refactor * 1000);
}