/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:34:48 by npillet           #+#    #+#             */
/*   Updated: 2026/07/01 15:37:55 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*monitor(void *arg)
{
	t_data		*data;
	long long	time;
	int			i;

	data = (t_data *)arg;
	i = 0;
	while (data->coder[i].finish != true || data->active_sim == true)
	{
		time = get_current_time(data) - data->coder->burnout_time;
		if (time >= data->time_burnout)
		{
			data->active_sim = false;
			if (data->coder[i].burnt == false)
			{
				printf(BURNOUT, get_current_time(data), data->coder->id);
				data->coder[i].burnt = true;
			}
		}
		i++;
	}
	return (NULL);
}
