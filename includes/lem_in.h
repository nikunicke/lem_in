/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:12:29 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/06 18:58:54 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

typedef	enum		e_command
{
	START,
	END
}					t_command;

typedef enum		e_category
{
	ANT,
	NODE,
	EDGE
}					t_category;

typedef struct		s_lem_in
{
	void			*h;
	void			*g;
	unsigned int	start;
	unsigned int	end;
	unsigned int	ants;
}					t_lem_in;

t_lem_in			*init_lem_in(void);
void				test(t_lem_in *data);

#endif
