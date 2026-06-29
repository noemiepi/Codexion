/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongles.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/26 13:50:53 by npillet           #+#    #+#             */
/*   Updated: 2026/06/29 10:44:29 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	take_dongle(t_coder *coder)
{
	if (try_take_dongle(coder->left_dongle, coder->data) == true)
	{
		if (coder->right_dongle == NULL)
			pthread_mutex_unlock(&coder->left_dongle->mutex_dongle);
		if (try_take_dongle(coder->right_dongle, coder->data) == true)
		{
			printf(DONGLE_TAKEN, get_current_time(coder->data), coder->id);
			printf(DONGLE_TAKEN, get_current_time(coder->data), coder->id);
		}
		else
			pthread_mutex_unlock(&coder->left_dongle->mutex_dongle);
	}
}

bool	try_take_dongle(t_dongle *dongle, t_data *data)
{
	if (get_current_time(data) >= dongle->cooldown)
	{
		pthread_mutex_lock(&dongle->mutex_dongle);
		return (true);
	}
	return (false);
}

void	release_dongle(t_coder *coder)
{
	long long	curr_time;

	curr_time = get_current_time(coder->data);
	if (coder->left_dongle != NULL)
	{
		coder->left_dongle->cooldown += curr_time;
		pthread_mutex_unlock(&coder->left_dongle->mutex_dongle);
	}
	if (coder->right_dongle != NULL)
	{
		coder->right_dongle->cooldown += curr_time;
		pthread_mutex_unlock(&coder->right_dongle->mutex_dongle);
	}
}
