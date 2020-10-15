/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:08:15 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/15 16:41:21 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

int		remaining_capacity(t_edge *e)
{
	return (e->capacity - e->flow);
}

int		equals(t_edge *e, int token)
{
	return (e->to->token == token);
}

void	visit_node(int **list, int node)
{
	(*list)[node] = 1;
}

int		bfs_internal(t_adjlist *graph, int start, int end, int token)
{
	t_list	*q_head;
	t_list	*q_part;
	t_list	*edge;
	int		*prev;
	int		*visit;

	prev = malloc(sizeof(int) * graph->size);
	visit = malloc(sizeof(int) * graph->size);
	ft_bzero(prev, graph->size);
	ft_bzero(visit, graph->size);
	q_head = NULL;
	ft_lstadd(&q_head, ft_lstcontent(&start));
	visit_node(&visit, start);
	while (q_head)
	{
		if (*(int *)q_head->content == end)
			break ;
		q_part = NULL;
		edge = graph->list[(*(int *)q_head->content)];
		while (edge)
		{
			if (remaining_capacity((t_edge *)edge->content) && !visit[((t_edge *)edge->content)->to->i])
			{
				ft_lstpush(&q_part, ft_lstcontent(&((t_edge *)edge->content)->to->i));
				prev[((t_edge *)edge->content)->to->i] = *(int *)q_head->content;
				visit_node(&visit, ((t_edge *)edge->content)->to->i);
			}
			edge = edge->next;
		}
		ft_lstpush(&q_head, q_part);
		q_head = q_head->next;
	}
	if (prev[end] == 0)
		return (0);
	int i = end;
	int j = 1;
	while ((i = prev[i]))
		j++;
	printf("j: %d\n", j);
	return (1);
}

int		bfs(t_adjlist *graph, int start, int end, int token)
{
	int	bfs;

	bfs = bfs_internal(graph, start, end, token);
	printf("result: %d\n", bfs);
	return (0);
}

void	edk(t_lem_in *data)
{
	bfs((t_adjlist *)data->g, data->start, data->end, 1);
}