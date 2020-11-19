/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:12:29 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/19 16:20:10 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "ft_hash.h"
# include "graph.h"

# define LEAKS 1
# define INPUT 1
# define COLOR_END 0
# define PRESULT 0
# define MAX_ANTS 2000000

typedef struct		s_lem_in
{
	t_hash			*h;
	t_graph			*g;
	int				start;
	int				end;
	unsigned int	ants;
}					t_lem_in;

t_lem_in			init_lem_in(void);

#endif
