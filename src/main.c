/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:32:45 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/08 17:20:16 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_hash.h"
#include "lexer.h"
#include "get_next_line.h"
#include "graph.h"
#include <stdio.h>

void	print_node(t_node *n, size_t s)
{
	printf("%s  -  %zu\n", n->id, s);
}

size_t	ft_hash2(t_node *n, size_t s)
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

int		main(void)
{
	t_lem_in	data;
	char		*line;
	size_t		s;
	t_token		*t;
	t_lexer		*l;

	data = *init_lem_in();
	data.h = init_hash_table(sizeof(t_list), ft_hash2);
	while ((s = ft_get_next_line(0, &line)) > 0)
	{
		l = init_lexer(line, s);
		while ((t = lex_get_next_token(l)))
			printf("token: {\n\ttype: %d\n\tlit: %s\n\tope: %c\n}\n\n", t->type, t->lit, t->ope);
	}
	// data.g = init_graph(((t_hash *)data.h)->used);
	// ft_map(data.h, print_node);
	return (0);
}
	// printf("g size: %zu\n", ((t_graph *)data.g)->vertices);
	// printf("data: {\n\tt_hash: %p\n\tt_graph: %p\n\tstart: %u\n\tend: %u\n\tants: %u\n}\n", data.h, data.g, data.start, data.end, data.ants);