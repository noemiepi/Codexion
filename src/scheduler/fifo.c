/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fifo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npillet <npillet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 11:47:24 by npillet           #+#    #+#             */
/*   Updated: 2026/06/29 16:02:01 by npillet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/codexion.h"

static t_fifo	*new_node(t_coder *coder);
static void		insert_node_back(t_fifo **lst, t_fifo *new);

void	scheduler_fifo(t_fifo fifo, t_coder *coder)
{
	;
}

static t_fifo	*new_node(t_coder *coder)
{
	t_fifo	*tmp;

	tmp = malloc(sizeof(t_fifo));
	if (tmp == NULL)
		return (NULL);
	tmp->data = coder;
	tmp->next = NULL;
	return (tmp);
}

static void	insert_node_back(t_fifo **lst, t_fifo *new)
{
	t_fifo	*current;

	if (*lst == NULL)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

static void	delete_node(t_fifo *node)
{
	free(node->data);
	free(node);
}
