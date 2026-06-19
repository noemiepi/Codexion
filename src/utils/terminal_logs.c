/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_logs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 18:39:07 by npillet           #+#    #+#             */
/*   Updated: 2026/06/19 19:47:42 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	terminal_logs(t_data *data)
{
	int	i;

	i = 0;
	printf(DONGLE_TAKEN, get_time(), data->coder[i].id);
	printf(COMPILING, get_time(), data->coder[i].id);
	printf(DEBUGGING, get_time(), data->coder[i].id);
	printf(REFRACTORING, get_time(), data->coder[i].id);
}
