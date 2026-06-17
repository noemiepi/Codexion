/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   codexion.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/12 10:49:27 by npillet           #+#    #+#             */
/*   Updated: 2026/06/17 10:40:36 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(t_data));
	if (!(parsing(argc, argv, &data)))
		return (FALSE);
	printf("Parsing completed!\n");
	init_coder(&data);
	debug_print_struct(&data);
	return (TRUE);
}
