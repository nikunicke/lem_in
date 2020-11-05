/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:20:38 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/05 14:51:05 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum	e_type
{
	NWL,
	ILLEGAL,
	IDENT,
	NUM,
	COMMAND,
	HYPH
}				t_type;

typedef struct	s_token
{
	t_type		type;
	char		*lit;
	char		ope;
	size_t		size;
}				t_token;

t_token			*new_token(t_type type, char *lit, char ope, size_t size);

#endif
