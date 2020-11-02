/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   costs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 17:15:58 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/02 16:32:05 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>
char	g_uninit_token;
# define UNINITIALZED ((void *)&g_uninit_token)

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
	}
	return (i_min - 1);
}

int		update_flow(int	*distribution, int flow)
{
	int		i;
	int		updated_flow;

	updated_flow = flow;
	i = 0;
	while (i < flow)
	{
		if (!--distribution[i++])
			updated_flow--;
	}
	return (updated_flow);
}

void		update_location(t_list **locations, t_list **set, int ants, int flow)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < ants)
	{
		if (j >= flow)
			j = 0;
		if (locations[i] == UNINITIALZED)
		{
			i++;
			j++;
			continue ;
		}
		if (!locations[i])
			locations[i] = set[j]->next;
		printf("L%d-%s ", i + 1, ((t_edge *)locations[i]->content)->from->id);
		locations[i] = locations[i]->next;
		if (!locations[i])
			locations[i] = UNINITIALZED;
		j++;
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
	t_list	**ant_loc;
	int		j;
	ant_loc = ft_malloctype(sizeof(t_list *), ants);
	int moving_ants;

	moving_ants = new_flow;
	while (ant_loc[moving_ants - 1] != UNINITIALZED)
	{
		update_location(ant_loc, set, moving_ants, new_flow);
		new_flow = update_flow(ants_per_path, new_flow);
		moving_ants += new_flow;
	}
	free(ant_loc);
	free(ants_per_path);
}

// cost could represent which path set we should use at which point? How do we account for previously "sent" ants?
// ants should increase with the flow value depending on which path set we use at that specific amount of ants?
// or calculate cost once for all sets.. for all ants? or just one ant? and when the ants fed into the lesser flow path set
// equals the cost of a bigger set, change set????
