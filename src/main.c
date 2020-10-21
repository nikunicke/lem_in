/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:32:45 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/21 16:38:48 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_hash.h"
#include "lexer.h"
#include "parser.h"
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
	t_lexer		l;
	t_parser	p;

	data = *init_lem_in();
	data.h = init_hash_table(sizeof(t_list), ft_hash2);
	while ((s = ft_get_next_line(0, &line)) > 0)
	{
		// ft_putendl(line);
		l = *new_lexer(line, s);
		p = *new_parser(&l);
		data.g = parser_parse(&p, &data);
	}
	edk(&data);
	// return (0);
	printf("\n\n");
	printf("ants: %u\n", data.ants);
	printf("start: %u\n", data.start);
	printf("end: %u\n", data.end);
	// printf("start-name: %s\n", (((t_list *)(t_adjlist **)data.g)->list[1])->content    )
	t_adjlist	*a;
	t_node		*snart;
	t_node		*send;
	a = (t_adjlist *)data.g;
	snart = ((t_edge *)(a->list[data.start]->content))->from;
	send = ((t_edge *)(a->list[data.end]->content))->from;
	printf("start-ID: %s\n", snart->id);
	printf("end-ID: %s\n", send->id);
	// ft_map(data.h, print_node);
	// printf("hash_used: %zu == %zu :graph_size\n", ((t_hash *)data.g)->used, ((t_graph *)data.g)->vertices);
	// system("leaks lem-in");
	return (0);
}
	// printf("g size: %zu\n", ((t_graph *)data.g)->vertices);
	// printf("data: {\n\tt_hash: %p\n\tt_graph: %p\n\tstart: %u\n\tend: %u\n\tants: %u\n}\n", data.h, data.g, data.start, data.end, data.ants);