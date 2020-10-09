/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:50:08 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/09 16:36:37 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdio.h>

t_parser		*init_parser(t_lexer *l)
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

void			parser_consume(t_parser *p, t_type type)
{
	if (p->current_token->type == type)
	{
		p->prev_token = p->current_token;
		p->current_token = lex_get_next_token(p->lex);
	}
	else
	{
		printf(
		"Error: Unexpected token '%s', with type %d\n",
		p->current_token->lit,
		p->current_token->type);
		exit(1);
	}
}

int			parse_hash(t_parser *p)
{
	if (p->current_token->type == HASH)
	{
		parser_consume(p, HASH);
		parser_consume(p, NWL);
		return (1);
	}
	return (0);
}

int				parse_ants(t_parser *p, t_stage *s)
{
	parser_consume(p, NUM);
	parser_consume(p, NWL);
	(*s)++;
	return (0);
}

void			parse_node(t_parser *p, t_stage *s)
{
	parser_consume(p, IDENT);
	if (p->current_token->type == HYPH)
	{
		parser_consume(p, HYPH);
		parser_consume(p, IDENT);
		return;
	}
	parser_consume(p, NUM);
	parser_consume(p, NUM);
	// parser_consume(p, NWL);
}

void			parser_parse(t_parser *p)
{
	static t_stage		stage;
	static t_command	start;
	static t_command	end;

	// printf("current: %s  --  %d\n", p->current_token->lit, p->current_token->type);
	if (parse_hash(p))
	{
		return ;
	}
	if (stage == ANTS)
		parse_ants(p, &stage);
	else if (stage == NODE)
		parse_node(p, &stage);
	else if (stage == EDGE){	
		printf("current: %s  --  %d\n", p->current_token->lit, p->current_token->type);
	}
}