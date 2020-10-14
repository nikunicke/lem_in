/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:08:15 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/14 17:53:24 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		remaining_capacity(t_edge *e)
{
	return (e->capacity - e->flow);
}

int		equals(t_edge *e, int token)
{
	return (e->to->token == token);
}

int		bfs_internal(t_adjlist *graph, int start, int end, int token)
{
	t_list	*q_head;
	t_list	*q_tail;
	t_list	*q_part;
	t_list	*edge;

	q_head = NULL;
	ft_lstadd(&q_head, ft_lstcontent(&start));
	q_tail = q_head;
	while (q_head)
	{
		q_part = NULL;
		edge = graph->list[(*(int *)q_head->content)];
		while (edge)
		{
			if (remaining_capacity((t_edge *)edge->content) && equals((t_edge *)edge->content, token))
			{
				ft_lstpush(&q_part, ft_lstcontent(((t_edge *)edge->content)->to));
				((t_edge *)edge->content)->to->token = token;
			}
			edge = edge->next;
		}
		ft_lstpush(&q_tail, q_part);
		q_tail = q_part;
		ft_lstpop(&q_head);
	}
	return (0);
}

int		bfs(t_adjlist **graph, int start, int end, int token)
{
	return (0);
}