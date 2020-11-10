/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:02:58 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/10 13:12:40 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "libft.h"
# include "token.h"

typedef struct	s_lexer
{
	char		*ch;
	size_t		s;
	size_t		i;
}				t_lexer;

t_lexer			new_lexer(char *content, size_t s);
t_token			*lex_get_next_token(t_lexer *l);
t_token			*lex_advance_token(t_lexer *l, t_token *t);
t_token			*lex_skip_comment(t_lexer *l);
void			lex_advance(t_lexer *l);
void			lex_skip_wsp(t_lexer *l);

#endif
