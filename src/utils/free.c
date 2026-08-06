/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:18:04 by npillet           #+#    #+#             */
/*   Updated: 2026/08/06 08:37:59 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	free_structures(t_data *data)
{
	free(data->coder);
	free(data->dongle);
	free(data->heap->node);
	free(data->queue);
	free(data->heap);
}
