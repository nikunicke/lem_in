/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:30:45 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/04 16:40:20 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "output.h"
#include <stdio.h>

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
		if (locations[i] == UNINITIALIZED)
		{
			i++;
			// j++;
			continue ;
		}
		if (!locations[i])
			locations[i] = set[j++]->next;
		// printf("L%d-%s ", i + 1, ((t_edge *)locations[i]->content)->from->id);
		write_ant_movement(i + 1, locations[i], ((t_edge *)locations[i]->content)->from->id);
		locations[i] = locations[i]->next;
		if (!locations[i])
			locations[i] = UNINITIALIZED;
		// j++;
		i++;
	}
	write(1, "\n", 1);
	// printf("\n");
}

int		*correct_offset(int *arr, int *flow, int total, int ants)
{
	int		i;
	int		start_flow;

	start_flow = *flow;
	i = start_flow - 1;
	while (total > ants)
	{
		if (arr[i] > 0)
		{
			if (!--arr[i])
				(*flow)--;
			total--;
		}
		if (!i)
			i = start_flow - 1;
		i--;
	}
	return (arr);
}

int		*distribute_ants(t_list **set, int *flow, int ants)
{
	float	cost;
	int		*ants_per_path;
	int		i;
	int		total;
	int		new_flow;

	total = 0;
	new_flow = 0;
	cost = get_cost(ants, *flow, set);
	printf("cost: %d\n", (int)cost);
	if (!(ants_per_path = ft_malloctype(sizeof(int), *flow)))
		return (NULL);
	i = (*flow) - 1;
	while (i > -1)
	{
		if (set[i]->content_size > cost)
		{
			ants_per_path[i--] = 0;
			new_flow++;
			continue ;
		}
		ants_per_path[i] = cost - set[i]->content_size + 1;
		total += ants_per_path[i--];
	}
	ants_per_path = correct_offset(ants_per_path, flow, total, ants);
	*flow -= new_flow;
	return (ants_per_path);
}

void	output_movement(t_list **set, int flow, int ants)
{
	int		*ants_per_path;
	t_list	**ant_loc;
	int		i;
	int moving_ants;

	// printf("flow: %d\n", flow);
	ants_per_path = distribute_ants(set, &flow, ants);
	i = 0;
	// while (i < flow)
	// {
	// 	printf("%d, ", ants_per_path[i]);
	// 	i++;
	// }
	// printf("\n");
	ant_loc = ft_malloctype(sizeof(t_list *), ants);
	moving_ants = flow;
	while (ant_loc[moving_ants - 1] != UNINITIALIZED)
	{
		update_location(ant_loc, set, moving_ants, flow);
		flow = update_flow(ants_per_path, flow);
		moving_ants += flow;
	}
	free(ant_loc);
	free(ants_per_path);
}
