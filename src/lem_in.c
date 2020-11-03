/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:21:31 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/03 13:02:49 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

size_t	lemin_hash(t_node *n, size_t s)
{
	char	*p;
	size_t	h;

	p = n->id;
	h = 0;
	while (s-- && *p)
	{
		h += *p;
		h = (h * *p) % (TABLE_SIZE);
		p++;
	}
	return (h);
}


t_lem_in	*init_lem_in(void)
{
	return (&(t_lem_in){
		.h = init_hash_table(sizeof(t_list), lemin_hash),
		.g = 0,
		.start = -1,
		.end = -1,
		.ants = 0,
	});
}
