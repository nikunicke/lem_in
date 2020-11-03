/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:32:45 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/03 13:10:52 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_hash.h"
#include "lexer.h"
#include "parser.h"
#include "get_next_line.h"
#include "graph.h"
#include <stdio.h>

void	validate_data(t_lem_in data)
{
	if (data.ants < 1 ||
		data.start == data.end ||
		data.start < 0 ||
		data.end < 0)
	{
		ft_putendl("Error: Insufficient data");
		exit(1);
	}
}

void	write_input(char *p, size_t s)
{
	p[s] =  '\n';
	write(1, p, s + 1);
	p[s] =  '\0';
}

void	parse(t_lem_in *data)
{
	char	*line;
	size_t	s;
	t_parser p;

	while ((s = ft_get_next_line(0, &line)) > 0)
	{
		if (INPUT)
			write_input(line, s);
		p = new_parser(new_lexer(line, s));
		parser_parse(&p, data);
	}
	if (s < 0)
	{
		ft_putendl_fd("Failed to read", 2);
		exit(1);
	}
	validate_data(*data);
}

int		main(void)
{
	t_lem_in	data;
	t_list		***paths;
	int			flow;

	data = *init_lem_in();
	parse(&data);
	paths = edk(&data);
	flow = min_cost_index(&data, paths);
	output_movement(paths[flow], flow + 1, data.ants);
	if (LEAKS)
		system("leaks lem-in");
	return (0);
}
