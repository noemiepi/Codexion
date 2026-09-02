/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 13:46:49 by npillet           #+#    #+#             */
/*   Updated: 2026/09/02 13:47:46 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	get_current_time(t_data *data)
{
	return (get_time() - data->start_sim);
}

bool	get_active_sim(t_data *data)
{
	bool	active;

	pthread_mutex_lock(&data->mutex_sim);
	active = data->active_sim;
	pthread_mutex_unlock(&data->mutex_sim);
	return (active);
}

bool	get_finished(t_coder *coder)
{
	bool	finished;

	pthread_mutex_lock(&coder->mutex_burnout);
	finished = coder->finish;
	pthread_mutex_unlock(&coder->mutex_burnout);
	return (finished);
}

long long	get_burnout(t_coder *coder)
{
	long long	burnout;

	burnout = 0;
	pthread_mutex_lock(&coder->mutex_burnout);
	burnout = coder->burnout_time;
	pthread_mutex_unlock(&coder->mutex_burnout);
	return (burnout);
}
