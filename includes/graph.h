/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:00:38 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/03 15:20:30 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  GRAPH_H
# define GRAPH_H
# include "ft_graph.h"

/*
**	graph.h implements functionality for ft_graph.h
*/

/*
**	t_edge implementations
*/
void	augment_path(t_edge **prev, int end);
int		remaining_capacity(t_edge *e);

/*
**	t_node implementations
*/
void	visit_node(t_edge *e, int token);
int		is_visited(t_node *node, int token);
int		is_in(t_node *node, t_edge *e);

#endif