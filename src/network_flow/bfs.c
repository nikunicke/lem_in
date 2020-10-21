/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 14:08:15 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/21 16:36:23 by npimenof         ###   ########.fr       */
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

void	augment(t_edge *e)
{
	e->flow += 1;
	e->residual->flow -= 1;
}

void	augment_path(t_edge **prev, int end)
{
	while (prev[end])
	{
		augment(prev[end]);
		end = prev[end]->from->i;
	}
}

t_list	*init_queue(void *head)
{
	t_list	*q;

	q = NULL;
	ft_lstadd(&q, ft_lstcontent(head));
	return (q);
}

void	*ft_memalloc2(size_t type, size_t s)
{
	char	*p;

	if (!(p = malloc(sizeof(type) * s)))
		return (NULL);
	ft_bzero(p, sizeof(type) * s);
	return (p);
}

int		is_visited(t_node *node, int token)
{
	return (node->token >= token);
}

t_list	*check_constraints(t_list *edge, t_edge **prev, int token)
{
	t_list	*q_part;

	q_part = NULL;
	while (edge)
	{
		if ((remaining_capacity((t_edge *)edge->content)) > 0 &&
			!is_visited(((t_edge *)edge->content)->to, token))
		{
			if (((t_edge *)edge->content)->flow < 0)
			{
				q_part = ft_lstcontent(&((t_edge *)edge->content)->to->i);
				prev[((t_edge *)edge->content)->to->i] = (t_edge *)edge->content;
				visit_node((t_edge *)edge->content, token);
				break ;
			}
			ft_lstpush(&q_part, ft_lstcontent(&((t_edge *)edge->content)->to->i));
			prev[((t_edge *)edge->content)->to->i] = (t_edge *)edge->content;
			visit_node((t_edge *)edge->content, token);
		}
		edge = edge->next;
	}
	return (q_part);
}

int		bfs_internal(t_adjlist *graph, t_node *start, t_node *end, int token)
{
	t_list	*q_head;
	t_edge	**prev;

	prev = ft_memalloc2(sizeof(t_edge *), graph->size);
	q_head = init_queue(&start->i);
	start->token = token;
	while (q_head && *(int *)q_head->content != end->i)
	{
		ft_lstpush(&q_head, check_constraints(graph->list[(*(int *)q_head->content)], prev, token));
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
	printf("%zu -- ", lst->content_size);
	while (lst)
	{
		printf("'%s' ", ((t_edge *)lst->content)->from->id);
		lst = lst->next;
	}
	printf("\n");
}

void	print_paths(t_adjlist *g, t_node *start, t_node *end, int token)
{
	t_list	*q_head;
	t_list	*edge;
	t_list	*path;
	t_list	*newpath;

	path = ft_lstcontent(g->list[start->i]->content);
	q_head = init_queue(path);
	while (q_head)
	{
		path = q_head->content;
		if (((t_edge *)path->content)->from->i == end->i)
			print_path(path);
		edge = g->list[((t_edge *)path->content)->from->i];
		while (edge)
		{
			if (!is_visited(((t_edge *)edge->content)->to, token) && ((t_edge *)edge->content)->flow == 1)
			{
				newpath = ft_lstclone(path, sizeof(t_edge *));
				ft_lstadd(&newpath, ft_lstcontent(g->list[((t_edge *)edge->content)->to->i]->content));
				newpath->content_size = path->content_size + 1;
				ft_lstpush(&q_head, ft_lstcontent(newpath));
				if (((t_edge *)edge->content)->to->i != end->i)
					visit_node((t_edge *)edge->content, token);
			}
			edge = edge->next;
		}
		q_head = q_head->next;
	}
}

int		bfs(t_lem_in *data, t_node *start, t_node *end)
{
	int	bfs;
	int	i;
	int	token;

	token = 1;
	i = 0;
	bfs = 0;
	while (i < data->ants && bfs_internal((t_adjlist *)data->g, start, end, token))
	{
		bfs++;
		token++;
		i++;
		print_paths((t_adjlist *)data->g, start, end, token);
		token++;
		printf("\n\n");
	}
	printf("result: %d\n", bfs);
	return (bfs);
}

void	edk(t_lem_in *data)
{
	t_node	*start;
	t_node	*end;

	start = ((t_edge *)((t_adjlist *)data->g)->list[data->start]->content)->from;
	end = ((t_edge *)((t_adjlist *)data->g)->list[data->end]->content)->from;
	bfs(data, start, end);
}