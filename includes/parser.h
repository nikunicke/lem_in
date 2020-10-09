/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 11:46:52 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/09 14:59:54 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
#include "lexer.h"

typedef enum	e_command
{
	START,
	END,
	UDF
}				t_command;

typedef enum	e_stage
{
	ANTS,
	NODE,
	EDGE,
}				t_stage;

typedef struct	s_parser
{
	t_stage		stage;
	t_lexer		*lex;
	t_token		*current_token;
	t_token		*prev_token;
}				t_parser;

t_parser		*init_parser(t_lexer *l);
void			parser_consume(t_parser *p, t_type type);
void			parser_parse(t_parser *p);
#endif