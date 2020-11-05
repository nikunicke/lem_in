/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:23:03 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/05 14:48:01 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

t_parser		new_parser(t_lexer l)
{
	t_token	t;

	t = *lex_get_next_token(&l);
	return ((t_parser){.stage = 0,
						.lex = &l,
						.current_token = t,
						.prev_token = t});
}

static void		error_out(char *lit, t_type got_type, t_type expect_type)
{
	char	**type_literals;

	type_literals = (char*[15]){
		"END OF LINE",
		"ILLEGAL",
		"IDENTIFIER",
		"NUMBER",
		"COMMAND",
		"HYPHEN",
	};
	write(2, RED "Error" RESET ": Unexpected token '", 36);
	ft_putstr_fd(lit, 2);
	write(2, "', with type " RED, 20);
	ft_putstr_fd(type_literals[got_type], 2);
	write(2, RESET ". Expected type " GREEN, 27);
	ft_putendl_fd(type_literals[expect_type], 2);
	write(2, RESET, 4);
	exit(1);
}

void			parser_consume(t_parser *p, t_type type)
{
	if (p->current_token.type == type)
	{
		p->prev_token = p->current_token;
		p->current_token = *lex_get_next_token(p->lex);
	}
	else
		error_out(p->current_token.lit, p->current_token.type, type);
}

t_command		parser_get_command(t_parser *p, t_stage *s)
{
	parser_consume(p, COMMAND);
	if (!ft_strcmp(p->prev_token.lit, "##start"))
		return (START);
	else if (!ft_strcmp(p->prev_token.lit, "##end"))
		return (END);
	return (UNDEFINED);
}

void			parser_edge_helper(t_parser *p, t_graph *g, t_hash *t)
{
	t_node	*s;
	t_node	*d;
	size_t	i;

	i = ft_hash(p->prev_token.lit, p->prev_token.size);
	s = ft_unique_node((t_list *)t->arr[i], p->prev_token.lit,
						p->prev_token.size);
	parser_consume(p, HYPH);
	if (p->current_token.type == NUM)
		parser_consume(p, NUM);
	else
		parser_consume(p, IDENT);
	i = ft_hash(p->prev_token.lit, p->prev_token.size);
	d = ft_unique_node((t_list *)t->arr[i], p->prev_token.lit,
						p->prev_token.size);
	add_edge(g, s, d);
	parser_consume(p, NWL);
	free(p->lex->ch - p->lex->s);
}
