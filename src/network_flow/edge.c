/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edge.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:54:28 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/03 15:03:49 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			remaining_capacity(t_edge *e)
{
	return (e->capacity - e->flow);
}

static void	augment(t_edge *e)
{
	e->flow += 1;
	e->from->in = 1;
	e->residual->flow -= 1;
}

void		augment_path(t_edge **prev, int end)
{
	while (prev[end])
	{
		augment(prev[end]);
		end = prev[end]->from->i;
	}
}
