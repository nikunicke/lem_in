/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 13:32:45 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/19 17:21:53 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "lexer.h"
#include "parser.h"
#include "get_next_line.h"
#include "edmons_karp.h"
#include "output.h"
#define RED "\033[0;31m"
#define RESET "\033[0m"

void	validate_data(t_lem_in data)
{
	if ((data.ants < 1 || data.ants > MAX_ANTS) ||
		data.start == data.end ||
		data.start < 0 ||
		data.end < 0 ||
		!data.g ||
		!((t_adjlist *)data.g)->list[data.start] ||
		!((t_adjlist *)data.g)->list[data.end])
	{
		ft_putstr(RED);
		ft_putstr("Error");
		ft_putstr(RESET);
		ft_putendl(": Insufficient data");
		exit(1);
	}
}

void	write_input(char *p, size_t s)
{
	p[s] = '\n';
	write(1, p, s + 1);
	p[s] = '\0';
}

void	parse(t_lem_in *data)
{
	char		*line;
	size_t		s;
	t_parser	p;
	t_lexer		l;

	while ((s = ft_get_next_line(0, &line)) > 0)
	{
		if (s - 1 == 0)
		{
			free(line);
			continue ;
		}
		if (INPUT)
			write_input(line, s - 1);
		l = new_lexer(line, s - 1);
		p = new_parser(&l);
		parser_parse(&p, data);
	}
	if (s < 0)
	{
		ft_putendl_fd("Error: Failed to read", 2);
		exit(1);
	}
	validate_data(*data);
}

int		main(void)
{
	t_lem_in	data;
	t_list		***paths;
	int			flow;
	int			result;

	data = init_lem_in();
	parse(&data);
	if (!(paths = edmons_karp(&data)))
		return (1);
	flow = min_cost_path(&data, paths);
	result = output_movement(paths[flow], flow + 1, data.ants);
	if (PRESULT)
	{
		ft_putstr("lines: ");
		ft_putnbr(result);
		write(1, "\n", 1);
	}
	if (LEAKS)
		system("leaks lem-in");
	exit(0);
	return (0);
}
