/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_logs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:39:07 by npillet           #+#    #+#             */
/*   Updated: 2026/06/22 21:22:03 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	terminal_logs(t_coder *coder)
{
	t_data	*data;
	
	data = coder->data;
	printf(DONGLE_TAKEN, get_current_time(data), coder->id);
	printf(COMPILING, get_current_time(data), coder->id);
	usleep(data->time_compile);
	printf(DEBUGGING, get_current_time(data), coder->id);
	usleep(data->time_debug);
	printf(REFACTORING, get_current_time(data), coder->id);
	usleep(data->time_refactor);
}
