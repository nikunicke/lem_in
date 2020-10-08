// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   test.c                                             :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2020/10/06 16:16:47 by npimenof          #+#    #+#             */
// /*   Updated: 2020/10/08 13:16:21 by npimenof         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "lem_in.h"
// #include "get_next_line.h"
// #include "graph.h"
// #include "ft_hash.h"
// #include <string.h>
// #include <stdio.h>
// #define RED "\033[0;31m"
// #define YELLOW "\033[0;33m"
// #define RESET "\033[0m"
// // reimplementation of strtok needed

// char	*ft_strtok(char *s, char *d)
// {
// 	static char	*p;
// 	int			i;

// 	if (!s)
// 	{
// 		if (!p || !*p)
// 			return (0);
// 		s = p;
// 	}
// 	i = ft_strcspn(s, d);
// 	if (*(s + i))
// 	{
// 		*(s + i) = 0;
// 		p = s + i + 1;
// 	}
// 	else
// 		p = 0;
// 	return (s);
// }

// t_ctg	next_ctg(t_ctg ctg)
// {
// 	return ((t_ctg)(ctg + 1));
// }

// void	tok(char *p, char *delim)
// {
// 	char	*t;

// 	t = strtok(p, delim);
// 	while (t)
// 	{
// 		t = strtok(NULL, delim);
// 	}
// }

// int		get_ants(char *p)
// {
// 	int		i;

// 	if (!(i = ft_atoi(p)))
// 	{
// 		printf(RED "Error" RESET ": Expected ants > 0. Got \"" YELLOW "%s" RESET "\".\n", p);
// 		exit(1);
// 	}
// 	return (i);
// }

// void	scan_edge(char *p)
// {
// 	return ;
// }

// void	scan_node(char *p)
// {
// 	char	*s;

// 	s = p;
// 	while (ft_isalnum(*s))
// 		s++;
// 	if (*s == '-')
// 		scan_edge(p);
// 	if (*s++ != ' ')
// 		printf(RED "Error" RESET ": Expected ' ', got " RED "%c\n" RESET, *s);
// 	while (ft_isdigit(*s))
// 		s++;
// 	if (*s++ != ' ')
// 		printf(RED "Error" RESET ": Expected ' ', got " RED "%c\n" RESET, *s);
// 	while (ft_isdigit(*s))
// 		s++;
// 	if (*s++ != 0)
// 		printf(RED "Error" RESET ": Expected '\\0', got " RED "%c\n" RESET, *s);
// }

// t_node	*get_node(char *p)
// {
// 	t_node	*n;
// 	char	*t;
// 	int		i;

// 	i = 0;
// 	t = strtok(p, " ");
// 	while (t)
// 	{
// 		if (i >= 3)
// 		{
// 			printf(RED "Error" RESET ": A node only supports two dimensional coordinates, got more\n");
// 			exit(1);
// 		}
// 		else if (!i)
// 			n = new_node(t);
// 		else if (i == 1)
// 			n->x = ft_atoi(t);
// 		else if (i == 2)
// 			n->y = ft_atoi(t);
// 		t = strtok(NULL, " ");
// 		i++;
// 	}
// 	if (i < 2)
// 	{
// 		printf("EDGE: %s\n", p);
// 		return (NULL); //leak
// 	}
// 	return (n);
// }

// void	test(t_lem_in *data)
// {
// 	size_t		len;
// 	t_node		*n;
// 	char		*p;
// 	t_ctg		ctg;

// 	ctg = 0;
// 	while ((len = ft_get_next_line(0, &p)) > 0)
// 	{
// 		if (*p == '#')
// 			continue ;
// 		else if (ctg == ANT)
// 		{
// 			data->ants = get_ants(p);
// 			ctg = next_ctg(ctg);
// 		}
// 		else if (ctg == NODE)
// 		{
// 			if (!(n = get_node(p)))
// 				ctg = next_ctg(ctg);
// 			else
// 				ft_insert(data->h, n, sizeof(t_node));
// 		}
// 		else if (ctg == EDGE)
// 		{
// 			printf("EDGE: %s\n", p);
// 			tok(p, "-");
// 		}
// 	}
// }

// void	scan_node2(char *s)
// {
// 	char	*tok;

// 	tok = ft_strtok(s, " ");
// 	while (tok)
// 	{
// 		printf("tok: %s\n", tok);
// 		tok = ft_strtok(0, " ");
// 	}
// }

// int		scan_ant(char *s)
// {
// 	size_t	a;

// 	a = ft_atoi(s);
// 	if (!a)
// 	{
// 		ft_putendl(RED "Error" RESET ": Expected ants, got");
// 		ft_putend(RED);
// 		ft_putend(s);
// 		ft_putend(RESET);
// 		exit(1);
// 	}
// 	return (a);
// }

// int		scan_command(char *s)
// {
// 	if (*(s + 1) != '#')
// 		return (COMMENT);
// 	s += 2;
// 	if (!ft_strcmp(s, "start"))
// 		return (START);
// 	else if (!ft_strcmp(s, "end"))
// 		return (END);
// 	return (ILLEGAL);
// }

// void	test2(t_lem_in *data)
// {
// 	int		len;
// 	char	*line;
// 	char	*tok;
// 	t_ctg	ctg;

// 	ctg = 0;
// 	while ((len = ft_get_next_line(0, &line)) > 0)
// 	{
// 		if (*line == '#')
// 		{
// 			if (scan_command == START && ctg == NODE)
// 				continue ;
// 		}
// 		else if (ctg == ANT && ctg++)
// 			data->ants = scan_ants(line);
// 		else if (ctg == NODE)
// 			scan_node2(line);
// 		break ;
// 	}
// }
