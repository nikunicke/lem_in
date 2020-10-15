/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:12:29 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/15 14:45:38 by npimenof         ###   ########.fr       */
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
void				test(t_lem_in *data);
void				test2(void);
void				edk(t_lem_in *data);

#endif
