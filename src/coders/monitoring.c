/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:34:48 by npillet           #+#    #+#             */
/*   Updated: 2026/07/03 16:01:39 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static bool	find_burnout(t_data *data, int *finish);

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
		time = get_current_time(data) - data->coder->burnout_time;
		if (get_finished(&data->coder[i]))
			(*finish)++;
		if (time >= data->time_burnout)
		{
			data->active_sim = false;
			pthread_mutex_lock(&data->mutex_print);
			printf(BURNOUT, get_current_time(data), data->coder->id);
			pthread_mutex_unlock(&data->mutex_print);
			return (true);
		}
		i++;
	}
	return (false);
}
