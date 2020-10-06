/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:32:45 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/06 18:57:37 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_hash.h"
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
	// CHECK NOTES

	t_lem_in	data;

	data = *init_lem_in();
	// printf("data: {\n\tt_hash: %p\n\tt_graph: %p\n\tstart: %u\n\tend: %u\n\tants: %u\n}\n", data.h, data.g, data.start, data.end, data.ants);
	// printf("Adding t_hash and t_graph pointers to domain data\n");
	data.h = init_hash_table(sizeof(t_list), ft_hash2);
	// data.g = init_graph(10);
	// printf("data: {\n\tt_hash: %p\n\tt_graph: %p\n\tstart: %u\n\tend: %u\n\tants: %u\n}\n", data.h, data.g, data.start, data.end, data.ants);
	// printf("data->h: {\n\tsize: %zu\n}\n", ((t_hash *)data.h)->size);
	// printf("data->g: {\n\tvertices: %zu\n}\n", ((t_graph *)data.g)->vertices);
	test(&data);
	printf("\n\n");
	printf("data: {\n\tt_hash: %p\n\tt_graph: %p\n\tstart: %u\n\tend: %u\n\tants: %u\n}\n", data.h, data.g, data.start, data.end, data.ants);
	printf("\n\n");
	ft_map(data.h, print_node);
	return (0);
}