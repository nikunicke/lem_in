/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 15:24:37 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/14 13:37:07 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "token.h"

t_token		*init_token(t_type type, char *lit, char ope, size_t size)
{
	t_token	*t;

	if (!(t = malloc(sizeof(t_token))))
		return (0);
	t->type = type;
	t->lit = lit;
	t->ope = ope;
	t->size = size;
	return (t);
}
