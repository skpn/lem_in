/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lem_structs_display.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:04:54 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/07 10:32:51 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

t_ant		**alloc_new_ants_tab(unsigned total_rooms)
{
	unsigned	cell;
	t_ant		**ants_tab;

	if (!(ants_tab = (t_ant **)gc_malloc(sizeof(t_ant *) * (total_rooms + 1))))
		return (NULL);
	cell = 0;
	while (cell < total_rooms)
	{
		if (!(ants_tab[cell] = (t_ant *)gc_malloc(sizeof(t_ant))))
			return (NULL);
		cell++;
	}
	return (ants_tab);
}

t_display	*alloc_new_display(unsigned total_rooms)
{
	t_display	*display;

	if (!(display = (t_display *)gc_malloc(sizeof(*display))))
		return (NULL);
	if (!(display->ants_tab = alloc_new_ants_tab(total_rooms)))
		return (NULL);
	display->last_id = 1;
	display->total_rooms = total_rooms;
	return (display);
}
