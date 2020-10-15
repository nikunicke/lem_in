/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:50:08 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/15 12:47:34 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include <stdio.h>
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

static char	*g_type_literals[6] = {
	"END OF LINE",
	"ILLEGAL",
	"IDENTIFIER",
	"NUMBER",
	"COMMAND",
	"HYPHEN"
};

t_node		*ft_unique_node(t_list *l, void *ptr, size_t s)
{
	while (l)
	{
		if (!(ft_memcmp(((t_node *)(l->content))->id, ptr, s)))
			return (l->content);
		l = l->next;
	}
	return (NULL);
}

t_parser	*new_parser(t_lexer *l)
{
	t_token	*t;

	t = lex_get_next_token(l);
	return (&(t_parser){.stage = 0,
						.lex = l,
						.current_token = t,
						.prev_token = t});
}

t_parser	*init_parser(t_lexer *l)
{
	t_parser	*p;

	if (!(p = malloc(sizeof(t_parser))))
		return (0);
	p->lex = l;
	p->current_token = lex_get_next_token(l);
	p->prev_token = p->current_token;
	p->stage = 0;
	return (p);
}

void		parser_consume(t_parser *p, t_type type)
{
	if (p->current_token->type == type)
	{
		p->prev_token = p->current_token;
		p->current_token = lex_get_next_token(p->lex);
	}
	else
	{
		printf(
		RED "Error" RESET ": Unexpected token '%s', with type" RED " %s" RESET ". Expected type" GREEN " %s\n" RESET,
		p->current_token->lit,
		g_type_literals[p->current_token->type],
		g_type_literals[type]);
		exit(1);
	}
}

int			parse_ants(t_parser *p, t_stage *s)
{
	int		n;

	parser_consume(p, NUM);
	n = ft_atoi(p->prev_token->lit);
	parser_consume(p, NWL);
	(*s)++;
	return (n);
}

void		edge_helper(t_parser *p, t_graph *g, t_hash *t)
{
	t_node	*s;
	t_node	*d;
	size_t	i;

	i = ft_hash(p->prev_token->lit, p->prev_token->size);
	s = ft_unique_node((t_list *)t->arr[i], p->prev_token->lit, p->prev_token->size);
	parser_consume(p, HYPH);
	if (p->current_token->type == NUM)
		parser_consume(p, NUM);
	else
		parser_consume(p, IDENT);
	i = ft_hash(p->prev_token->lit, p->prev_token->size);
	d = ft_unique_node((t_list *)t->arr[i], p->prev_token->lit, p->prev_token->size);
	add_edge(g, s, d);
	parser_consume(p, NWL);
}

t_node		*parse_node(t_parser *p, t_stage *s, t_graph **g, t_hash *t)
{
	t_node	*n;

	if (p->current_token->type == NUM)
		parser_consume(p, NUM);
	else
		parser_consume(p, IDENT);
	if (p->current_token->type == HYPH)
	{
		*g = init_graph(t->used);
		edge_helper(p, *g, t);
		(*s)++;
		return (NULL);
	}
	n = new_node(p->prev_token->lit);
	parser_consume(p, NUM);
	n->x = ft_atoi(p->prev_token->lit);
	parser_consume(p, NUM);
	n->y = ft_atoi(p->prev_token->lit);
	parser_consume(p, NWL);
	return (n);
}

void		parse_edge(t_parser *p, t_graph *g, t_hash *t)
{
	t_node	*s;
	t_node	*d;
	size_t	i;

	if (p->current_token->type == NUM)
		parser_consume(p, NUM);
	else
		parser_consume(p, IDENT);
	edge_helper(p, g, t);
}

t_command	parse_hash(t_parser *p, t_stage *s)
{
	parser_consume(p, COMMAND);
	if (!ft_strcmp(p->prev_token->lit, "##start"))
		return (START);
	else if (!ft_strcmp(p->prev_token->lit, "##end"))
		return (END);
	return (UNDEFINED);
}

t_graph		*parser_parse(t_parser *p, t_lem_in *data)
{
	static t_stage		stage;
	static t_command	start;
	static t_command	end;
	t_command			tmp;

	if (p->current_token->type)
	{
		if (p->current_token->type == COMMAND)
		{
			tmp = parse_hash(p, &stage);
			if (!start && tmp == START)
			{
				data->start = ((t_hash *)data->h)->used;
				start++;
			}
			else if (!end && tmp == END)
			{
				data->end = ((t_hash *)data->h)->used;
				end++;
			}
			else
				exit(1);
		}
		else if (stage == ANTS)
			data->ants = parse_ants(p, &stage);
		else if (stage == NODE)
			ft_insert(data->h, parse_node(p, &stage, (t_graph **)&data->g,
				data->h), sizeof(t_node));
		else if (stage == EDGE)
			parse_edge(p, data->g, data->h);
	}
	return (data->g);
}
