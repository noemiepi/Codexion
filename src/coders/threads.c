/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:39:38 by npillet           #+#    #+#             */
/*   Updated: 2026/06/29 10:45:24 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_create(&data->monitoring_id, NULL, monitor, data);
	while (data->nb_coders != i)
	{
		pthread_create(&data->coder[i].thread_id, NULL, coders_action,
			&data->coder[i]);
		i++;
	}
}

void	join_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_join(data->monitoring_id, NULL);
	while (data->nb_coders != i)
	{
		pthread_join(data->coder[i].thread_id, NULL);
		i++;
	}
}
