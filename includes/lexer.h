/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:02:58 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/09 16:37:26 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H
# include "lem_in.h"
# include "libft.h"
# include "token.h"

typedef struct	s_lexer
{
	char		*ch;
	size_t		s;
	size_t		i;
	// char		ch;
}				t_lexer;

t_lexer			*init_lexer(char *content, size_t s);
void			update_lexer(t_lexer *l, char *content, size_t s);
// t_lexer			*new_lexer(char *content, size_t s);
t_token			*lex_get_next_token(t_lexer *l);
t_token			*lex_advance_token(t_lexer *l, t_token *t);
t_token			*lex_ident(t_lexer *l);
t_token			*lex_hash(t_lexer *l);
void			lex_advance(t_lexer *l);
void			lex_skip_wsp(t_lexer *l);

#endif