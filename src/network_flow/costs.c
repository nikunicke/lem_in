// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   costs.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2020/10/22 17:15:58 by npimenof          #+#    #+#             */
// /*   Updated: 2020/11/04 14:31:44 by npimenof         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "output.h"
// #include <stdio.h>

// float	get_cost(int ants, int flow, t_list **l)
// {
// 	float	cost;
// 	int		i;

// 	i = 0;
// 	cost = 0;
// 	while (i < flow)
// 		cost += l[i++]->content_size;
// 	return ((cost + ants - 1) / flow);
// }

// int		min_cost_path(t_lem_in *data, t_list ***paths)
// {
// 	t_list	***tmp;
// 	int		i;
// 	int		i_min;
// 	float	cost;
// 	float	min_cost;

// 	tmp = paths;
// 	i = 1;
// 	i_min = 0;
// 	cost = 0;
// 	min_cost = INT32_MAX;
// 	while (*tmp)
// 	{
// 		cost = get_cost(data->ants, i, *tmp);
// 		if (cost < min_cost)
// 		{
// 			min_cost = cost;
// 			i_min = i;
// 		}
// 		i++;
// 		tmp++;
// 	}
// 	return (i_min - 1);
// }

// int		update_flow(int	*distribution, int flow)
// {
// 	int		i;
// 	int		updated_flow;

// 	updated_flow = flow;
// 	i = 0;
// 	while (i < flow)
// 	{
// 		if (!--distribution[i++])
// 			updated_flow--;
// 	}
// 	return (updated_flow);
// }

// void		update_location(t_list **locations, t_list **set, int ants, int flow)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	while (i < ants)
// 	{
// 		if (j >= flow)
// 			j = 0;
// 		if (locations[i] == UNINITIALIZED)
// 		{
// 			i++;
// 			j++;
// 			continue ;
// 		}
// 		if (!locations[i])
// 			locations[i] = set[j]->next;
// 		printf("L%d-%s ", i + 1, ((t_edge *)locations[i]->content)->from->id);
// 		locations[i] = locations[i]->next;
// 		if (!locations[i])
// 			locations[i] = UNINITIALIZED;
// 		j++;
// 		i++;
// 	}
// 	printf("\n");
// }

// int		*correct_offset(int *arr, int *flow, int total, int ants)
// {
// 	int		i;

// 	i = (*flow) - 1;
// 	while (total > ants)
// 	{
// 		if (arr[i] > 0)
// 		{
// 			if (!--arr[i])
// 				(*flow)--;
// 			total--;
// 		}
// 		if (!i)
// 			i = (*flow) - 1;
// 		i--;
// 	}
// 	return (arr);
// }

// int		*distribute_ants(t_list **set, int *flow, int ants)
// {
// 	float	cost;
// 	int		*ants_per_path;
// 	int		i;
// 	int		total;

// 	total = 0;
// 	cost = get_cost(ants, *flow, set);
// 	if (!(ants_per_path = ft_malloctype(sizeof(int), *flow)))
// 		return (NULL);
// 	i = (*flow) - 1;
// 	while (i > -1)
// 	{
// 		if (set[i]->content_size > cost)
// 		{
// 			ants_per_path[i--] = 0;
// 			(*flow)--;
// 			continue ;
// 		}
// 		ants_per_path[i] = cost - set[i]->content_size + 1;
// 		total += ants_per_path[i--];
// 	}
// 	i = (*flow) - 1;
// 	return (correct_offset(ants_per_path, flow, total, ants));
// }

// void	output_movement(t_list **set, int flow, int ants)
// {
// 	int		*ants_per_path;
// 	t_list	**ant_loc;
// 	int		j;
// 	int moving_ants;

// 	ants_per_path = distribute_ants(set, &flow, ants);
// 	ant_loc = ft_malloctype(sizeof(t_list *), ants);
// 	moving_ants = flow;
// 	while (ant_loc[moving_ants - 1] != UNINITIALIZED)
// 	{
// 		update_location(ant_loc, set, moving_ants, flow);
// 		flow = update_flow(ants_per_path, flow);
// 		moving_ants += flow;
// 	}
// 	free(ant_loc);
// 	free(ants_per_path);
// }
