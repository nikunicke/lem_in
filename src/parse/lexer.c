/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 13:56:52 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/12 15:49:20 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "token.h"
#include <stdio.h>

t_lexer		*init_lexer(char *content, size_t s)
{
	t_lexer		*lex;

	if (!(lex = malloc(sizeof(t_lexer))))
		return (0);
	lex->s = s;
	lex->i = 0;
	lex->ch = content;
	return (lex);
}

void		update_lexer(t_lexer *l, char *content, size_t s)
{
	l->s = s;
	l->ch = content;
	l->i = 0;
}

// t_lexer		*new_lexer(char *content, size_t s)
// {
// 	return ((&(t_lexer){content, s, 0, content[0]}));
// }

void		lex_advance(t_lexer *l)
{
	if (l->i < l->s)
	{
		l->i++;
		l->ch++;
	}
}

void		lex_skip_wsp(t_lexer *l)
{
	while (ft_iswhitespace(*(l->ch)))
		lex_advance(l);
}

void		lex_skip_comment(t_lexer *l)
{
	while (*(l->ch))
		lex_advance(l);
}

void		lex_skip_zero(t_lexer *l)
{
	if (l->i < l->s && *(l->ch) == 0)
		lex_advance(l);
}

t_token		*lex_get_next_token(t_lexer *l)
{
	while (l->i < l->s)
	{
		lex_skip_wsp(l);
		if (*(l->ch) == '#')
		{
			if (*(l->ch + 1) == '#')
				return (lex_hash(l));
			else
				lex_skip_comment(l);
		}
		else if (*(l->ch) == '-')
			return (lex_advance_token(l, init_token(HYPH, NULL, *(l->ch), 1)));
		else if (ft_isalnum(*(l->ch)))
			return (lex_ident(l));
		return (init_token(NWL, 0, 0, 0));
	}
	return (init_token(NWL, 0, 0, 0));
}

t_token		*lex_advance_token(t_lexer *l, t_token *t)
{
	lex_advance(l);
	return (t);
}

t_token		*lex_ident(t_lexer *l)
{
	char	*id;
	size_t	i;

	i = 0;
	id = l->ch;
	while (ft_isdigit(*(l->ch)) && ++i)
		lex_advance(l);
	if (*(l->ch) == 0 || *(l->ch) == ' ')
		return (init_token(NUM, id, 0, i));
	while (ft_isalnum(*(l->ch)) && ++i)
		lex_advance(l);
	if (*(l->ch) == ' ')
	{
		*(l->ch) = 0;
		lex_advance(l);
	}
	return (init_token(IDENT, id, 0, i));
}

t_token		*lex_hash(t_lexer *l)
{
	char	*lit;
	size_t	i;

	i = 0;
	lit = l->ch;
	while (l->i < l->s && ++i)
		lex_advance(l);
	return (init_token(COMMAND, lit, 0, i));
}