/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:32:45 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/02 18:39:38 by npimenof         ###   ########.fr       */
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
	int			flow;
	size_t		s;
	t_lexer		l;
	t_parser	p;
	t_list		***paths;

	data = *init_lem_in();
	data.h = init_hash_table(sizeof(t_list), ft_hash2);
	while ((s = ft_get_next_line(0, &line)) > 0)
	{
		ft_putendl(line);
		l = *new_lexer(line, s);
		p = *new_parser(&l);
		parser_parse(&p, &data);
	}
	paths = edk(&data);
	flow = min_cost_index(&data, paths);
	output_movement(paths[flow], flow + 1, data.ants);
	if (LEAKS)
		system("leaks lem-in");
	return (0);
}
