/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 12:53:42 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/05 14:50:35 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OUTPUT_H
# define OUTPUT_H
# include "lem_in.h"
# include "graph.h"

char	g_uninit_token;
# define UNINITIALIZED ((void *)&g_uninit_token)

void	write_ant_movement(int ant, t_list *location, char *room);
int		min_cost_path(t_lem_in *data, t_list ***paths);
int		output_movement(t_list **set, int flow, int ants);
float	get_cost(int ants, int fow, t_list **l);
int		min_cost_path(t_lem_in *data, t_list ***paths);

#endif
