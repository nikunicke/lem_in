/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:32:13 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/19 18:24:47 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void			lex_advance(t_lexer *l)
{
	if (l->i < l->s)
	{
		l->i++;
		l->ch++;
	}
}

static t_token	lex_ident(t_lexer *l)
{
	char	*id;
	size_t	i;

	i = 0;
	id = l->ch;
	while (ft_isdigit(*(l->ch)) && ++i)
		lex_advance(l);
	if (*(l->ch) == 0 || *(l->ch) == ' ')
	{
		*(l->ch) = 0;
		lex_advance(l);
		return (new_token(NUM, id, 0, i));
	}
	while (!ft_iswhitespace(*(l->ch)) && *(l->ch) != '-' && l->i < l->s && ++i)
		lex_advance(l);
	if (*(l->ch) == ' ')
	{
		*(l->ch) = 0;
		lex_advance(l);
	}
	return (new_token(IDENT, id, 0, i));
}

static t_token	lex_hash(t_lexer *l)
{
	char	*lit;
	size_t	i;

	i = 0;
	lit = l->ch;
	while (l->i < l->s && ++i)
		lex_advance(l);
	return (new_token(COMMAND, lit, 0, i));
}

t_token			lex_get_next_token(t_lexer *l)
{
	while (l->i < l->s)
	{
		if (lex_skip_wsp(l))
			break ;
		if (*(l->ch) == '#')
		{
			if (*(l->ch + 1) == '#')
				return (lex_hash(l));
			else
				return (lex_skip_comment(l));
		}
		else if (*(l->ch) == '-')
			return (lex_advance_token(l, new_token(HYPH, NULL, *(l->ch), 1)));
		else if (ft_isalnum(*(l->ch)))
		{
			return (lex_ident(l));
		}
		return (new_token(NWL, 0, 0, 0));
	}
	return (new_token(NWL, 0, 0, 0));
}
