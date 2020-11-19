/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:33:22 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/19 18:24:03 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_lexer		new_lexer(char *content, size_t s)
{
	return ((t_lexer){
		.ch = content,
		.s = s,
		.i = 0
	});
}

t_token		new_token(t_type type, char *lit, char ope, size_t size)
{
	return ((t_token){
		.type = type,
		.lit = lit,
		.ope = ope,
		.size = size
	});
}

int		lex_skip_wsp(t_lexer *l)
{
	while (ft_iswhitespace(*(l->ch)))
		lex_advance(l);
	if (!*l->ch)
	{
		free(l->ch - l->i);
		return (1);
	}
	return (0);
}

t_token		lex_skip_comment(t_lexer *l)
{
	free(l->ch - l->i);
	return (new_token(NWL, 0, 0, 0));
}

t_token		lex_advance_token(t_lexer *l, t_token t)
{
	lex_advance(l);
	return (t);
}
