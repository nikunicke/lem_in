/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:54:44 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/10 13:13:28 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"
#include "edmons_karp.h"

static void		advance(t_adjlist *g, t_list *path, t_list *edge, t_list **q)
{
	t_list	*newpath;

	newpath = ft_lstclone(path);
	ft_lstadd(&newpath,
			ft_lstcontent(g->list[((t_edge *)edge->content)->to->i]->content));
	newpath->content_size = path->content_size + 1;
	ft_lstpush(q, ft_lstcontent(newpath));
}

static int		edge_ok(t_list *edge, int start, int token)
{
	if (!is_visited(((t_edge *)edge->content)->to, token) &&
				((t_edge *)edge->content)->flow == -1)
	{
		if (((t_edge *)edge->content)->to->i != start)
			visit_node((t_edge *)edge->content, token);
		return (1);
	}
	return (0);
}

static t_list	**save_path(t_list **set, t_list **path, int start)
{
	if (!(((t_edge *)(*path)->content)->from->i == start))
		return (set);
	*set++ = *path;
	*path = NULL;
	return (set);
}

t_list			**save_path_set(t_adjlist *g, t_node *s, t_node *e, int token)
{
	t_list	*q_head;
	t_list	*edge;
	t_list	*path;
	t_list	**path_set;

	path_set = ft_malloctype(sizeof(t_list *), token / 2);
	path = ft_lstcontent(g->list[e->i]->content);
	q_head = init_queue(path);
	while (q_head)
	{
		path = q_head->content;
		ft_lstpop(&q_head);
		edge = g->list[((t_edge *)path->content)->from->i];
		path_set = save_path(path_set, &path, s->i);
		while (edge)
		{
			if (edge_ok(edge, s->i, token))
				advance(g, path, edge, &q_head);
			edge = edge->next;
		}
		ft_lstdel(&path, NULL);
	}
	return (path_set - (token / 2));
}
