/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:21:54 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/10 13:15:31 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int		parse_ants(t_parser *p, t_stage *s)
{
	int		n;

	parser_consume(p, NUM);
	n = ft_atoi(p->prev_token.lit);
	parser_consume(p, NWL);
	(*s)++;
	free(p->lex->ch - p->lex->s);
	return (n);
}

static t_node	*parse_node(t_parser *p, t_stage *s, t_graph **g, t_hash *t)
{
	t_node	*n;

	if (p->current_token.type == NUM)
		parser_consume(p, NUM);
	else
		parser_consume(p, IDENT);
	if (p->current_token.type == HYPH)
	{
		*g = init_graph(t->used);
		parser_edge_helper(p, *g, t);
		(*s)++;
		return (NULL);
	}
	if (ft_unique_node(
		(t_list *)t->arr[ft_hash(p->prev_token.lit, p->prev_token.size)],
		p->prev_token.lit, p->prev_token.size))
		return (NULL);
	n = new_node(p->prev_token.lit);
	parser_consume(p, NUM);
	n->x = ft_atoi(p->prev_token.lit);
	parser_consume(p, NUM);
	n->y = ft_atoi(p->prev_token.lit);
	parser_consume(p, NWL);
	return (n);
}

static void		parse_edge(t_parser *p, t_graph *g, t_hash *t)
{
	t_node	*s;
	t_node	*d;
	size_t	i;

	if (p->current_token.type == NUM)
		parser_consume(p, NUM);
	else
		parser_consume(p, IDENT);
	parser_edge_helper(p, g, t);
}

static void		parse_command(t_parser *p, t_lem_in *data, t_stage *stage)
{
	t_command			command;
	static t_command	start;
	static t_command	end;

	command = parser_get_command(p, stage);
	if (!start && command == START)
	{
		data->start = ((t_hash *)data->h)->used;
		start++;
	}
	else if (!end && command == END)
	{
		data->end = ((t_hash *)data->h)->used;
		end++;
	}
	else if (command != START && command != END)
		return ;
	else
	{
		ft_putendl_fd("Error: Only 1 start and 1 end allowed", 2);
		exit(1);
	}
	free(p->lex->ch - p->lex->s);
}

void			parser_parse(t_parser *p, t_lem_in *data)
{
	static t_stage		stage;
	t_node				*n;

	if (p->current_token.type)
	{
		if (p->current_token.type == COMMAND)
			parse_command(p, data, &stage);
		else if (stage == ANTS)
			data->ants = parse_ants(p, &stage);
		else if (stage == NODE)
		{
			if (!(n = parse_node(p, &stage, (t_graph **)&data->g, data->h)) &&
				stage == NODE)
				free(p->prev_token.lit);
			ft_insert(data->h, n, sizeof(t_node));
		}
		else if (stage == EDGE)
			parse_edge(p, data->g, data->h);
	}
}
