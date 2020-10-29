/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:08:15 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/29 16:32:31 by npimenof         ###   ########.fr       */
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

void	visit_node(t_edge *e, int token)
{
	e->to->token = token;
}

void	unvisit_node(t_edge *e)
{
	e->from->token--;
}

void	augment(t_edge *e)
{
	e->flow += 1;
	e->from->in = 1;
	e->residual->flow -= 1;
}

void	augment_path(t_edge **prev, int end)
{
	// int	e;

	// e = end;
	while (prev[end])
	{
		augment(prev[end]);
		end = prev[end]->from->i;
	}
	// prev[end]->to->in = 0;
}

t_list	*init_queue(void *head)
{
	t_list	*q;

	q = NULL;
	ft_lstadd(&q, ft_lstcontent(head));
	return (q);
}

int		is_visited(t_node *node, int token)
{
	return (node->token >= token);
}

int		is_in(t_node *node, t_edge *e)
{
	if (!e)
		return (0);
	if (node->in == 1 && e->flow == 0)
		return (1);
	return (0);
}

int		check_prio(t_list *edge, int token, int remaining_cap)
{
	// printf("WHAT THE FK?\n");
	// printf("\t\t\t\t%p\n", edge);
	int	limit;

	limit = 1;
	if (remaining_cap > 1)
		limit = 0;
	while (edge)
	{
		// printf("edge: '%s' --> '%s'\n", ((t_edge *)edge->content)->from->id, ((t_edge *)edge->content)->to->id);
		if ((remaining_capacity((t_edge *)edge->content)) > limit &&
			!is_visited(((t_edge *)edge->content)->to, token))
		{
			return (1);
		}
		edge = edge->next;
	}
	return (0);
}

t_list	*check_constraints(t_adjlist *g, t_list *edge, t_edge **prev, int token)
{
	t_list	*q_part;
	int		prio;
	int		lim;
	int		rcap;

	q_part = NULL;
	prio = 0;
	// lim = ((t_edge *)edge->content)->from->in;
	lim = 0;
	if (prev[((t_edge *)edge->content)->from->i])
		lim = is_in(((t_edge *)edge->content)->from, prev[((t_edge *)edge->content)->from->i]);
		// lim = prev[((t_edge *)edge->content)->from->i]->flow;
	// printf("\tlim: %d\n", lim);
	while (edge)
	{
		// printf("'%s' --> '%s'\n", ((t_edge *)edge->content)->from->id, ((t_edge *)edge->content)->to->id);
		// printf("\tin: %d\n", ((t_edge *)edge->content)->to->in);
		// prio = is_in(((t_edge *)edge->content)->to, prev[((t_edge *)edge->content)->from->i]); !!!!!!!!!!!!!
		prio = is_in(((t_edge *)edge->content)->to, ((t_edge *)edge->content));
		// if (!prio)
		// 	lim = 1;
		// printf("\tprio: %d\n", prio);
		// printf("--> '%s'\n", ((t_edge *)edge->content)->to->id);
		// 	q_part = NULL;
		// 	if (!is_visited(((t_edge *)edge->content)->to, token))
		// 	{
		// 		q_part = ft_lstcontent(&((t_edge *)edge->content)->to->i); // leek
		// 		prev[((t_edge *)edge->content)->to->i] = (t_edge *)edge->content;
		// 		visit_node((t_edge *)edge->content, token);
		// 	}
		// 	break ;
		// }
		// !is_in(((t_edge *)edge->content)->to, ((t_edge *)edge->content)->flow)
		if ((rcap = remaining_capacity((t_edge *)edge->content)) > lim &&
			!is_visited(((t_edge *)edge->content)->to, token))
		{
			// printf("\tadding edge: '%s' --> '%s'\n", ((t_edge *)edge->content)->from->id, ((t_edge *)edge->content)->to->id);
			// if (((t_edge *)edge->content)->flow < 0)
			// {
			// 	q_part = ft_lstcontent(&((t_edge *)edge->content)->to->i); // leek
			// 	prev[((t_edge *)edge->content)->to->i] = (t_edge *)edge->content;
			// 	visit_node((t_edge *)edge->content, token);
			// 	break ;
			// }
			// instead of the following trickery in check_prio, we could change the functionality
			// the visited token, by separating the visited state depending on if we use a residual edge
			// or not. However, the residuals we use right now, are sort of fake, they also work as normal
			// edges... now focus on the output...
			if (prio == 1 && !check_prio(g->list[((t_edge *)edge->content)->to->i], token, rcap))
			{
				// printf("\tdiscarding: %s\n", (((t_edge *)edge->content)->to->id));
				edge = edge->next;
			// visit_node((t_edge *)edge->content, token);
				continue ;
			}
			// printf("\tprio: %d\tadding edge: '%s' --> '%s'\n", prio, ((t_edge *)edge->content)->from->id, ((t_edge *)edge->content)->to->id);
			visit_node((t_edge *)edge->content, token);
			ft_lstpush(&q_part, ft_lstcontent(&((t_edge *)edge->content)->to->i));
			prev[((t_edge *)edge->content)->to->i] = (t_edge *)edge->content;
		}
		edge = edge->next;
	}
	return (q_part);
}

int		bfs_internal(t_adjlist *graph, t_node *start, t_node *end, int token)
{
	t_list	*q_head;
	t_edge	**prev;

	prev = ft_malloctype(sizeof(t_edge *), graph->size);
	q_head = init_queue(&start->i);
	start->token = token;
	while (q_head && *(int *)q_head->content != end->i)
	{
		start->in = 0;
		// printf("q_head: %s\n", ((t_edge *)graph->list[(*(int *)q_head->content)]->content)->from->id);
		ft_lstpush(&q_head, check_constraints(graph, graph->list[(*(int *)q_head->content)], prev, token));
		q_head = q_head->next;
		//lstpop here instead of nexting
	}
	if (!prev[end->i])
		return (0);
	augment_path(prev, end->i);
	free(prev);
	prev = NULL;
	return (1);
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

t_list	**save_path_set(t_adjlist *g, t_node *start, t_node *end, int token)
{
	t_list	*q_head;
	t_list	*edge;
	t_list	*path;
	t_list	*newpath;
	t_list	**path_set;
	int		i;
	int		e;

	i = 0;
	path_set = ft_malloctype(sizeof(t_list *), token / 2);
	path = ft_lstcontent(g->list[end->i]->content);
	q_head = init_queue(path);
	while (q_head)
	{
		path = q_head->content;
		if (((t_edge *)path->content)->from->i == start->i)
		{
			print_path(path);
			path_set[i] = path;
			i++;
			// printf("\n");
		}
		edge = g->list[((t_edge *)path->content)->from->i];
		// e = 0;
		// if (((t_edge *)path->content)->from->i != start->i)
			// printf("from: '%s'\n", ((t_edge *)g->list[((t_edge *)path->content)->from->i]->content)->from->id);
		while (edge)
		{
			if (!is_visited(((t_edge *)edge->content)->to, token) && ((t_edge *)edge->content)->flow == -1)
			{
				newpath = ft_lstclone(path, sizeof(t_edge *));
				ft_lstadd(&newpath, ft_lstcontent(g->list[((t_edge *)edge->content)->to->i]->content));
				newpath->content_size = path->content_size + 1;
				ft_lstpush(&q_head, ft_lstcontent(newpath));
				if (((t_edge *)edge->content)->to->i != start->i)
					visit_node((t_edge *)edge->content, token);
				// e++;
				// if (e > 1 && ((t_edge *)edge->content)->from->i != start->i)
				// {
					// printf("from: '%s'\n", ((t_edge *)g->list[((t_edge *)path->content)->from->i]->content)->from->id);
					// printf("\t'%s' --> '%s'\n", ((t_edge *)edge->content)->from->id, ((t_edge *)edge->content)->to->id);
				// }			
			}
			// if (e > 1 && ((t_edge *)edge->content)->from->i != start->i)
				// printf("\n");
			edge = edge->next;
		}
		// if (e > 1 && ((t_edge *)edge->content)->from->i != end->i)
		// 	printf("\n");
		// if (e > 1)
		// {
		// 	printf("'%s' --> '%s'\n", ((t_edge *)edge->content)->from->id, ((t_edge *)edge->content)->to->id);
		// }
		// printf("%d", e);
		q_head = q_head->next;
	}
	printf("\n\n\n");
	return (path_set);
}

t_list		***bfs(t_lem_in *data, t_node *start, t_node *end)
{
	int		bfs;
	int		token;
	t_list	***collection;

	if (!(collection = (t_list ***)ft_malloctype(sizeof(t_list **), data->ants + 1)))
		return (0);
	token = 1;
	bfs = 0;
	while (bfs < data->ants &&
			bfs_internal((t_adjlist *)data->g, start, end, token))
	{
		token++;
		collection[bfs] = save_path_set((t_adjlist *)data->g, start, end, token);
		token++;
		bfs++;
		// printf("\n\n");
	}
	// printf("bfs: %d\n", bfs);
	return (collection);
}

t_list	***edk(t_lem_in *data)
{
	t_node	*start;
	t_node	*end;

	start = ((t_edge *)((t_adjlist *)data->g)->list[data->start]->content)->from;
	end = ((t_edge *)((t_adjlist *)data->g)->list[data->end]->content)->from;
	return (bfs(data, start, end));
}