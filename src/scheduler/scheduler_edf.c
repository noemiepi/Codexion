/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler_edf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 14:28:05 by npillet           #+#    #+#             */
/*   Updated: 2026/06/30 11:21:33 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

// static t_edf	*new_node(int burnout);
// static t_edf	*insert_node(t_edf *node, int burnout);

void	scheduler_edf(t_coder *coder)
{
	printf("(s'en fout)%p\n", coder);
}

// static t_edf	*new_node(int burnout)
// {
// 	t_edf	*node;

// 	node = malloc(sizeof(t_edf));
// 	if (node == NULL)
// 		return (NULL);
// 	node->data = burnout;
// 	node->left = NULL;
// 	node->right = NULL;
// 	return (node);
// }

// static t_edf	*insert_node(t_edf *node, int burnout)
// {
// 	if (node == NULL)
// 		return (new_node(burnout));
// 	if (burnout < node->data)
// 		node->left = insert(node->left, burnout);
// 	else if (burnout > node->data)
// 		node->left = insert(node->right, burnout);
// 	return (node);
// }
