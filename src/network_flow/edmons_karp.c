/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmons_karp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:08:15 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/19 15:30:47 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "edmons_karp.h"

static int		check_prio(t_list *edge, int token, int remaining_cap)
{
	int	limit;

	limit = 1;
	if (remaining_cap > 1)
		limit = 0;
	while (edge)
	{
		if ((remaining_capacity((t_edge *)edge->content)) > limit &&
			!is_visited(((t_edge *)edge->content)->to, token))
		{
			return (1);
		}
		edge = edge->next;
	}
	return (0);
}

static t_list	*check_edges(t_adjlist *g, t_list *e, t_edge **prev, int token)
{
	t_list	*q_part;
	int		prio;
	int		lim;
	int		rcap;

	q_part = NULL;
	lim = 0;
	if (prev[((t_edge *)e->content)->from->i])
		lim = is_in(((t_edge *)e->content)->from,
					prev[((t_edge *)e->content)->from->i]);
	while (e)
	{
		prio = is_in(((t_edge *)e->content)->to, ((t_edge *)e->content));
		if ((rcap = remaining_capacity((t_edge *)e->content)) > lim &&
			!is_visited(((t_edge *)e->content)->to, token))
		{
			if (!(prio == 1 &&
				!check_prio(g->list[((t_edge *)e->content)->to->i],
							token, rcap)))
				add_to_q(&q_part, e, prev, token);
		}
		e = e->next;
	}
	return (q_part);
}

static int		bfs_internal(t_adjlist *g, t_node *s, t_node *e, int token)
{
	t_list	*q_head;
	t_edge	**prev;
	int		ret;

	ret = 0;
	if (!(prev = ft_malloctype(sizeof(t_edge *), g->size)))
		return (0);
	q_head = init_queue(&s->i);
	s->token = token;
	while (q_head && *(int *)q_head->content != e->i)
	{
		s->in = 0;
		ft_lstpush(&q_head, check_edges(g,
					g->list[(*(int *)q_head->content)], prev, token));
		ft_lstpop(&q_head);
	}
	ft_lstdel(&q_head, NULL);
	if (prev[e->i] && ++ret)
		augment_path(prev, e->i);
	free(prev);
	prev = NULL;
	return (ret);
}

static t_list	***bfs(t_lem_in *data, t_node *start, t_node *end)
{
	int		bfs;
	int		token;
	t_list	***collection;

	if (!(collection = (t_list ***)ft_malloctype(sizeof(t_list **),
			data->ants + 1)))
		return (NULL);
	token = 1;
	bfs = 0;
	while (bfs < data->ants &&
			bfs_internal((t_adjlist *)data->g, start, end, token))
	{
		token++;
		collection[bfs] = save_path_set((t_adjlist *)data->g, start,
											end, token);
		token++;
		bfs++;
	}
	if (!bfs)
	{
		ft_putendl("Error: No paths");
		exit(1);
	}
	return (collection);
}

t_list			***edmons_karp(t_lem_in *data)
{
	t_node	*s;
	t_node	*e;

	if (!data || !data->g)
		return (NULL);
	s = ((t_edge *)((t_adjlist *)data->g)->list[data->start]->content)->from;
	e = ((t_edge *)((t_adjlist *)data->g)->list[data->end]->content)->from;
	return (bfs(data, s, e));
}
