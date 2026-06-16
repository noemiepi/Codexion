/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_coders.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 14:04:53 by npillet           #+#    #+#             */
/*   Updated: 2026/06/16 16:03:03 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	create_coder(t_data *data, t_coder *coder, int i);
static void	create_dongle(t_dongle *dongle, int i);

void	*init_coder(t_data *data)
{
	int	i;

	i = 0;
	data->coder = malloc(sizeof(t_coder) * data->nb_coders);
	if (data->coder == NULL)
		return (NULL);
	data->dongle = malloc(sizeof(t_dongle) * data->nb_coders);
	if (data->dongle == NULL)
		return (NULL);
	while (data->nb_coders != i)
	{
		create_coder(data, &data->coder[i], i);
		create_dongle(&data->dongle[i], i);
		i++;
	}
	return(NULL);
}

static void	create_coder(t_data *data, t_coder *coder, int i)
{
	coder->id = i;
	coder->nb_compile = 0;
	coder->burnout_time = data->time_burnout;
	coder->finish = 0;
	coder->left_dongle = 0;
	coder->right_dongle = 0;
}

static void	create_dongle(t_dongle *dongle, int i)
{
	dongle->id = i;
	dongle->cooldown = 0;
}
