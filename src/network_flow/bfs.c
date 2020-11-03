/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:08:15 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/03 16:52:05 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "graph.h"
#include "edmons_karp.h"
#include <stdio.h>

t_list	*init_queue(void *head)
{
	t_list	*q;

	q = NULL;
	ft_lstadd(&q, ft_lstcontent(head));
	return (q);
}

int		check_prio(t_list *edge, int token, int remaining_cap)
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

void	add_edge_to_q(t_list **q_part, t_list *edge, t_edge **prev, int token)
{
	visit_node((t_edge *)edge->content, token);
	ft_lstpush(q_part, ft_lstcontent(&((t_edge *)edge->content)->to->i));
	prev[((t_edge *)edge->content)->to->i] = (t_edge *)edge->content;
}

t_list	*check_constraints(t_adjlist *g, t_list *edge, t_edge **prev, int token)
{
	t_list	*q_part;
	int		prio;
	int		lim;
	int		rcap;

	q_part = NULL;
	lim = 0;
	if (prev[((t_edge *)edge->content)->from->i])
		lim = is_in(((t_edge *)edge->content)->from,
					prev[((t_edge *)edge->content)->from->i]);
	while (edge)
	{
		prio = is_in(((t_edge *)edge->content)->to, ((t_edge *)edge->content));
		if ((rcap = remaining_capacity((t_edge *)edge->content)) > lim &&
			!is_visited(((t_edge *)edge->content)->to, token))
		{
			if (!(prio == 1 && !check_prio(g->list[((t_edge *)edge->content)->to->i],
											token, rcap)))
				add_edge_to_q(&q_part, edge, prev, token);
		}
		edge = edge->next;
	}
	return (q_part);
}

int		bfs_internal(t_adjlist *graph, t_node *start, t_node *end, int token)
{
	t_list	*q_head;
	t_edge	**prev;
	int		ret;

	ret = 0;
	prev = ft_malloctype(sizeof(t_edge *), graph->size);
	q_head = init_queue(&start->i);
	start->token = token;
	while (q_head && *(int *)q_head->content != end->i)
	{
		start->in = 0;
		ft_lstpush(&q_head, check_constraints(graph,
					graph->list[(*(int *)q_head->content)], prev, token));
		ft_lstpop(&q_head);
	}
	ft_lstdel(&q_head, NULL);
	if (prev[end->i] && ++ret)
		augment_path(prev, end->i);
	free(prev);
	prev = NULL;
	return (ret);
}

void	print_path(t_list *lst)
{
	printf("%zu\t-- ", lst->content_size);
	while (lst)
	{
		printf("'%s' ", ((t_edge *)lst->content)->from->id);
		lst = lst->next;
	}
	printf("\n");
}

// t_list	**save_path_set(t_adjlist *g, t_node *start, t_node *end, int token)
// {
// 	t_list	*q_head;
// 	t_list	*edge;
// 	t_list	*path;
// 	t_list	*newpath;
// 	t_list	**path_set;
// 	int		i;
// 	int		e;

// 	i = 0;
// 	path_set = ft_malloctype(sizeof(t_list *), token / 2);
// 	path = ft_lstcontent(g->list[end->i]->content);
// 	q_head = init_queue(path);
// 	while (q_head)
// 	{
// 		path = q_head->content;
// 		ft_lstpop(&q_head);
// 		if (((t_edge *)path->content)->from->i == start->i)
// 		{
// 			path_set[i] = path;
// 			i++;
// 			continue;
// 		}
// 		edge = g->list[((t_edge *)path->content)->from->i];
// 		while (edge)
// 		{
// 			if (!is_visited(((t_edge *)edge->content)->to, token) && ((t_edge *)edge->content)->flow == -1)
// 			{
// 				newpath = ft_lstclone(path);
// 				ft_lstadd(&newpath, ft_lstcontent(g->list[((t_edge *)edge->content)->to->i]->content));
// 				newpath->content_size = path->content_size + 1;
// 				ft_lstpush(&q_head, ft_lstcontent(newpath));
// 				if (((t_edge *)edge->content)->to->i != start->i)
// 					visit_node((t_edge *)edge->content, token);
// 			}
// 			edge = edge->next;
// 		}
// 		ft_lstdel(&path, NULL);
// 	}
// 	return (path_set);
// }

t_list		***bfs(t_lem_in *data, t_node *start, t_node *end)
{
	int		bfs;
	int		token;
	t_list	***collection;

	if (!(collection = (t_list ***)ft_malloctype(sizeof(t_list **),
			data->ants + 1)))
		return (0);
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
	return (collection);
}

t_list	***edk(t_lem_in *data)
{
	t_node	*s;
	t_node	*e;

	s = ((t_edge *)((t_adjlist *)data->g)->list[data->start]->content)->from;
	e = ((t_edge *)((t_adjlist *)data->g)->list[data->end]->content)->from;
	return (bfs(data, s, e));
}