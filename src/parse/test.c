/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 16:16:47 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/06 19:09:41 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"
#include "graph.h"
#include "ft_hash.h"
#include <string.h>
#include <stdio.h>
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"
// reimplementation of strtok needed

t_category	next_ctg(t_category ctg)
{
	return ((t_category)(ctg + 1));
}

void	tok(char *p, char *delim)
{
	char	*t;

	t = strtok(p, delim);
	while (t)
	{
		// printf("t: %s\n", t);
		t = strtok(NULL, delim);
	}
}

int		get_ants(char *p)
{
	int		i;

	if (!(i = ft_atoi(p)))
	{
		printf(RED "Error" RESET ": Expected ants > 0. Got \"" YELLOW "%s" RESET "\".\n", p);
		exit(1);
	}
	return (i);
}

t_node	*get_node(char *p)
{
	t_node	*n;
	char	*t;
	int		i;

	i = 0;
	t = strtok(p, " ");
	while (t)
	{
		if (i >= 3)
		{
			printf(RED "Error" RESET ": A node only supports two dimensional coordinates, got more\n");
			exit(1);
		}
		else if (!i)
			n = new_node(t);
		else if (i == 1)
			n->x = ft_atoi(t);
		else if (i == 2)
			n->y = ft_atoi(t);
		t = strtok(NULL, " ");
		i++;
	}
	if (i < 2)
	{
		printf("EDGE: %s\n", p);
		return (NULL); //leak
	}
	return (n);
}

void	test(t_lem_in *data)
{
	size_t		len;
	t_node		*n;
	char		*p;
	t_category	ctg;

	ctg = 0;
	while ((len = ft_get_next_line(0, &p)) > 0)
	{
		if (*p == '#')
			continue ;
		else if (ctg == ANT)
		{
			data->ants = get_ants(p);
			ctg = next_ctg(ctg);
		}
		else if (ctg == NODE)
		{
			if (!(n = get_node(p)))
				ctg = next_ctg(ctg);
			else
				ft_insert(data->h, n, sizeof(t_node));
		}
		else if (ctg == EDGE)
		{
			printf("EDGE: %s\n", p);
			tok(p, "-");
		}
	}
}
