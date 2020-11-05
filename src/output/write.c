/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:33:15 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/05 13:45:28 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

void	write_ant_movement(int ant, t_list *location, char *room)
{
	if (!location->next && COLOR_END)
		write(1, GREEN, 7);
	write(1, "L", 1);
	ft_putnbr(ant);
	write(1, "-", 1);
	ft_putstr(room);
	write(1, " ", 1);
	if (!location->next && COLOR_END)
		write(1, RESET, 4);
}
