/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 14:21:31 by npimenof          #+#    #+#             */
/*   Updated: 2020/10/06 15:19:33 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_lem_in	*init_lem_in(void)
{
	return (&(t_lem_in){0, 0, 0, 0, 0});
}