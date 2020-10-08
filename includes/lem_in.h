/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:12:29 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/08 16:00:04 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

// typedef struct		s_token
// {
// 	int				id;
// 	char			*lit;
// }					t_token;

// typedef enum		e_ctg
// {
// 	ANT,
// 	NODE,
// 	EDGE
// }					t_ctg;

// typedef enum		e_command
// {
// 	ILLEGAL,
// 	COMMENT,
// 	START,
// 	END
// }					t_command;

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
void				test2(void);

#endif
