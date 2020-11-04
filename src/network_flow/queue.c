/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 11:44:04 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/04 11:47:32 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graph.h"

t_list	*init_queue(void *head)
{
	t_list	*q;

	q = NULL;
	ft_lstadd(&q, ft_lstcontent(head));
	return (q);
}

void	add_to_q(t_list **q_part, t_list *edge, t_edge **prev, int token)
{
	visit_node((t_edge *)edge->content, token);
	ft_lstpush(q_part, ft_lstcontent(&((t_edge *)edge->content)->to->i));
	prev[((t_edge *)edge->content)->to->i] = (t_edge *)edge->content;
}
