/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_getter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 13:46:49 by npillet           #+#    #+#             */
/*   Updated: 2026/06/22 20:21:01 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

long long	get_current_time(t_data data)
{
	return (get_time() - data.start_sim);
}
