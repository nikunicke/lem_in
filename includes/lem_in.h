/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:12:29 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/29 16:10:02 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "ft_hash.h"
# include "graph.h"

typedef struct		s_lem_in
{
	t_hash			*h;
	t_graph			*g;
	unsigned int	start;
	unsigned int	end;
	unsigned int	ants;
}					t_lem_in;

t_lem_in			*init_lem_in(void);
t_list				***edk(t_lem_in *data);
float				get_cost(int ants, int flow, t_list **l);
int					min_cost_index(t_lem_in *data, t_list ***paths);
void				print_path(t_list *lst);
void				output_movement(t_list **set, int flow, int ants);


#endif
