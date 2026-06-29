/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:28:05 by npillet           #+#    #+#             */
/*   Updated: 2026/06/29 15:58:27 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static t_edf	*new_node(int burnout);
static t_edf	*insert_node(t_edf *node, int burnout);

void	scheduler_edf(t_coder *coder)
{
	;
}

static t_edf	*new_node(int burnout)
{
	t_edf	*tmp;

	tmp = malloc(sizeof(t_fifo));
	if (tmp == NULL)
		return (NULL);
	tmp->data = burnout;
	tmp->left = NULL;
	tmp->right = NULL;
	return (tmp);
}

static t_edf	*insert_node(t_edf *node, int burnout)
{
	if (node == NULL)
		return (new_node(burnout));
	if (burnout < node->data)
		node->left = insert(node->left, burnout);
	else if (burnout > node->data)
		node->left = insert(node->right, burnout);
	return (node);
}
