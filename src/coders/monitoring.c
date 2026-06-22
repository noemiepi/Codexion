/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 10:34:48 by npillet           #+#    #+#             */
/*   Updated: 2026/06/22 20:00:10 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*monitor(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	data->start_sim = get_time();
	printf("monitoring\n");
	return (NULL);
}
