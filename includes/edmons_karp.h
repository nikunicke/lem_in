/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmons_karp.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 15:59:33 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/03 16:52:58 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef  EDMONS_KARP_H
# define EDMONS_KARP_H
# include "graph.h"
# include "lem_in.h"

t_list		***edk(t_lem_in *data);
t_list		**save_path_set(t_adjlist *g, t_node *start, t_node *end, int token);
t_list		*init_queue(void *head);

#endif