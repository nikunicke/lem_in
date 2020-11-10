/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:30:45 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/10 10:57:36 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"

static int	update_flow(int *distribution, int flow)
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

static void	update_location(t_list **locations,
							t_list **set, int ants, int flow)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < ants)
	{
		if (j >= flow)
			j = 0;
		if (locations[i] == UNINITIALIZED)
		{
			i++;
			continue ;
		}
		if (!locations[i])
			locations[i] = set[j++]->next;
		write_ant_movement(i + 1, locations[i],
							((t_edge *)locations[i]->content)->from->id);
		locations[i] = locations[i]->next;
		if (!locations[i])
			locations[i] = UNINITIALIZED;
		i++;
	}
	write(1, "\n", 1);
}

static int	*correct_offset(int *arr, int *flow, int total, int ants)
{
	int		i;
	int		start_flow;

	start_flow = *flow;
	i = start_flow - 1;
	while (total > ants)
	{
		if (arr[i] > 0)
		{
			arr[i]--;
			if (!arr[i])
				(*flow)--;
			total--;
		}
		if (!i)
			i = *flow;
		i--;
	}
	return (arr);
}

static int	*distribute_ants(t_list **set, int *flow, int ants)
{
	float	cost;
	int		*ants_per_path;
	int		i;
	int		total;

	total = 0;
	cost = get_cost(ants, *flow, set);
	if (!(ants_per_path = ft_malloctype(sizeof(int), *flow)))
		return (NULL);
	i = (*flow) - 1;
	while (i > -1)
	{
		if (set[i]->content_size > cost)
		{
			ants_per_path[i--] = 0;
			(*flow)--;
			continue ;
		}
		ants_per_path[i] = cost - set[i]->content_size + 1;
		total += ants_per_path[i--];
	}
	return (correct_offset(ants_per_path, flow, total, ants));
}

int			output_movement(t_list **set, int flow, int ants)
{
	int		*ants_per_path;
	t_list	**ant_loc;
	int		moving_ants;
	int		steps;

	ants_per_path = distribute_ants(set, &flow, ants);
	ant_loc = ft_malloctype(sizeof(t_list *), ants);
	moving_ants = flow;
	steps = 0;
	write(1, "\n", 1);
	while (ant_loc[moving_ants - 1] != UNINITIALIZED)
	{
		update_location(ant_loc, set, moving_ants, flow);
		flow = update_flow(ants_per_path, flow);
		moving_ants += flow;
		steps++;
	}
	free(ant_loc);
	free(ants_per_path);
	return (steps);
}
