/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:49:27 by npillet           #+#    #+#             */
/*   Updated: 2026/07/02 10:02:46 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (!(parsing(argc, argv, &data)))
		return (false);
	printf("Parsing completed!\n\n");
	init_structures(&data);
	create_mutexes(&data);
	data.start_sim = get_time();
	create_threads(&data);
	join_threads(&data);
	destroy_mutexes(&data);
	free_structures(&data);
	return (true);
}
