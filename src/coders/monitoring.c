/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:34:48 by npillet           #+#    #+#             */
/*   Updated: 2026/09/01 15:31:39 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static bool	find_burnout(t_data *data, int *finish);
static void	stop_sim(t_data *data);

void	*monitor(void *arg)
{
	t_data	*data;
	int		finish;

	data = (t_data *)arg;
	while (get_active_sim(data) == true)
	{
		finish = 0;
		if (find_burnout(data, &finish))
			return (NULL);
		if (finish == data->nb_coders)
		{
			stop_sim(data);
			pthread_mutex_lock(&data->mutex_print);
			printf(END);
			pthread_mutex_unlock(&data->mutex_print);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

static bool	find_burnout(t_data *data, int *finish)
{
	long long	time;
	int			i;

	i = 0;
	while (data->nb_coders != i)
	{
		pthread_mutex_lock(&data->coder[i].mutex_burnout);
		time = get_current_time(data) - data->coder[i].burnout_time;
		pthread_mutex_unlock(&data->coder[i].mutex_burnout);
		if (get_finished(&data->coder[i]))
			(*finish)++;
		else if (time >= data->time_burnout)
		{
			stop_sim(data);
			pthread_mutex_lock(&data->mutex_print);
			printf(BURNOUT, get_current_time(data), data->coder[i].id);
			pthread_mutex_unlock(&data->mutex_print);
			return (true);
		}
		i++;
	}
	return (false);
}

static void	stop_sim(t_data *data)
{
	pthread_mutex_lock(&data->mutex_sim);
	data->active_sim = false;
	pthread_mutex_unlock(&data->mutex_sim);
	pthread_mutex_lock(&data->heap->mutex_heap);
	pthread_cond_broadcast(&data->heap->cond_heap);
	pthread_mutex_unlock(&data->heap->mutex_heap);
	pthread_mutex_lock(&data->queue->mutex_queue);
	pthread_cond_broadcast(&data->queue->cond_queue);
	pthread_mutex_unlock(&data->queue->mutex_queue);
}
