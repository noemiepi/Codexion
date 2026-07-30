/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:18:04 by npillet           #+#    #+#             */
/*   Updated: 2026/07/30 11:46:51 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	free_structures(t_data *data)
{
	free(data->dongle);
	free(data->coder);
	free(data->queue);
	free(data->heap);
}
