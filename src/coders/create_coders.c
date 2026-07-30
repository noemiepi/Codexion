/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_coders.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 14:04:53 by npillet           #+#    #+#             */
/*   Updated: 2026/07/30 10:03:02 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static void	*create_coders(t_data *data);
static void	init_coder(t_data *data, t_coder *coder, int i);
static void	init_dongle(t_dongle *dongle, int i);
static void	assign_dongle(t_data *data, int i);

void	*init_structures(t_data *data)
{
	pthread_t	monitoring;

	monitoring = 0;
	data->monitoring_id = monitoring;
	data->active_sim = true;
	data->queue = malloc(sizeof(t_queue));
	if (data->queue == NULL)
		return (NULL);
	data->queue->front = NULL;
	data->queue->rear = NULL;
	data->heap = malloc(sizeof(t_heap));
	if (data->heap == NULL)
		return (NULL);
	data->heap->node = NULL;
	data->heap->size = 0;
	create_coders(data);
	return (NULL);
}

static void	*create_coders(t_data *data)
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
		init_coder(data, &data->coder[i], i);
		init_dongle(&data->dongle[i], i);
		assign_dongle(data, i);
		i++;
	}
	return (NULL);
}

static void	init_coder(t_data *data, t_coder *coder, int i)
{
	pthread_t	thread;

	thread = i;
	coder->data = data;
	coder->id = i;
	coder->nb_compile = 0;
	coder->burnout_time = data->time_burnout;
	coder->finish = false;
	coder->left_dongle = NULL;
	coder->right_dongle = NULL;
	coder->thread_id = thread;
}

static void	init_dongle(t_dongle *dongle, int i)
{
	dongle->id = i;
	dongle->cooldown = 0;
}

static void	assign_dongle(t_data *data, int i)
{
	int	next_i;

	next_i = (i + 1) % data->nb_coders;
	if (data->nb_coders > 1)
	{
		data->coder[i].left_dongle = &data->dongle[i];
		data->coder[i].right_dongle = &data->dongle[next_i];
	}
	else
		data->coder[i].left_dongle = &data->dongle[i];
}
