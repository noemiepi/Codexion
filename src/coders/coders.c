/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coders.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 14:36:10 by npillet           #+#    #+#             */
/*   Updated: 2026/06/22 20:16:31 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

void	*coders_action(void *arg)
{
	t_coder	*coder;

	coder = (t_coder *)arg;
	terminal_logs(coder);
	return (NULL);
}
