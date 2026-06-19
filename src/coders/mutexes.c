/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:56:04 by npillet           #+#    #+#             */
/*   Updated: 2026/06/19 19:33:10 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	create_mutexes(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_init(&data->mutex_print, NULL);
	while (data->nb_coders != i)
	{
		pthread_mutex_init(&data->dongle[i].mutex_dongle, NULL);
		i++;
	}
}
