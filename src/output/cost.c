/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cost.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:28:21 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/10 13:13:43 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

float	get_cost(int ants, int flow, t_list **l)
{
	float	cost;
	int		i;

	i = 0;
	cost = 0;
	while (i < flow)
		cost += l[i++]->content_size;
	return ((cost + ants - 1) / flow);
}

int		min_cost_path(t_lem_in *data, t_list ***paths)
{
	t_list	***tmp;
	int		i;
	int		i_min;
	float	cost;
	float	min_cost;

	tmp = paths;
	i = 1;
	i_min = 0;
	cost = 0;
	min_cost = INT32_MAX;
	while (*tmp)
	{
		cost = get_cost(data->ants, i, *tmp);
		if (cost < min_cost)
		{
			min_cost = cost;
			i_min = i;
		}
		i++;
		tmp++;
	}
	return (i_min - 1);
}
