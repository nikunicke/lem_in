/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   costs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:15:58 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/28 17:50:20 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

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

int		min_cost_index(t_lem_in *data, t_list ***paths)
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
		printf("cost: %f\n", cost);
	}
	return (i_min - 1);
}

void	three_sixty_flip(t_list **set, int *ants, int flow, int moving_ants)
{
	int		i;
	int		new_flow;
	
	i = 0;
	new_flow = flow;
	while (i < flow)
	{
		if (!--ants[i])
			new_flow--;
		i++;
	}
	if (!new_flow)
		return ;
	// printf("\t\t\t%d\n", new_flow);
	// three_sixty_flip(set, ants, new_flow, moving_ants - new_flow);
	printf("wtf: %d\n", moving_ants - flow);
	i = moving_ants - flow;
	while (i < moving_ants)
	{
		printf("L%d-%s ", i + 1, ((t_edge *)set[i]->content)->from->id);
		i++;
	}
	printf("\n");
}

void	output_movement(t_list **set, int flow, int ants)
{
	float	cost;
	int		*ants_per_path;
	int		i;
	int		total;
	int		new_flow;

	cost = get_cost(ants, flow, set);
	if (!(ants_per_path = ft_malloctype(sizeof(int), flow)))
		return ;
	i = 0;
	total = 0;
	new_flow = flow;
	// printf("cost: %f\n", cost);
	i = flow - 1;
	while (i > -1)
	{
		if (set[i]->content_size > cost)
		{
			ants_per_path[i] = 0;
			new_flow--;
			i--;
			continue ;
		}
		ants_per_path[i] = cost - set[i]->content_size + 1;
		total += ants_per_path[i];
		i--;
	}
	printf("total: %d\n", total);
	i = flow;
	while (total > ants)
	{
		if (ants_per_path[i] > 0)
		{
			if (!--ants_per_path[i])
				new_flow--;
			total--;
		}
		if (!i)
			i = flow - 1;
		i--;
	}
	i = 0;
	while (i < flow)
	{
		printf("path%d len: %zu -- ants: %d\n", i, set[i]->content_size, ants_per_path[i]);
		// if (ants_per_path[i])
		// 	new_flow++;
		i++;
	}
	printf("ants: %d\n", ants);
	// three_sixty_flip(set, ants_per_path, new_flow, ants);

	// char	***step;
	// int		moving_ants;

	// step = ft_malloctype(sizeof(char **), cost + 1);
	// i = 0;
	// while (i < (int)cost)
	// {
	// 	moving_ants = ((i + 1) * flow);
	// 	step[i] = ft_malloctype(sizeof(char *), new_flow + 1);
	// 	i++;
	// }
	// i = 0;
	// while (i < new_flow)
	// {
	// 	printf("L%d-%s ", i + 1, ((t_edge *)set[i]->content)->from->id);
	// 	i++;
	// }

}

// cost could represent which path set we should use at which point? How do we account for previously "sent" ants?
// ants should increase with the flow value depending on which path set we use at that specific amount of ants?
// or calculate cost once for all sets.. for all ants? or just one ant? and when the ants fed into the lesser flow path set
// equals the cost of a bigger set, change set????
