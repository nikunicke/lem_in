/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:12:29 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/04 16:40:38 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "ft_hash.h"
# include "graph.h"

# define LEAKS 0
# define INPUT 0
# define COLOR_END 1

typedef struct		s_lem_in
{
	t_hash			*h;
	t_graph			*g;
	int				start;
	int				end;
	unsigned int	ants;
}					t_lem_in;

t_lem_in			*init_lem_in(void);

#endif
