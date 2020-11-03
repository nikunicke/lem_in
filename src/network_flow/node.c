/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:57:38 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/03 14:59:53 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	visit_node(t_edge *e, int token)
{
	e->to->token = token;
}

int		is_visited(t_node *node, int token)
{
	return (node->token >= token);
}

int		is_in(t_node *node, t_edge *e)
{
	if (!e)
		return (0);
	if (node->in == 1 && e->flow == 0)
		return (1);
	return (0);
}
