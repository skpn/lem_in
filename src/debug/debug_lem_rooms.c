/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lem_rooms.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:17:42 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/07 16:27:35 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	print_relatives(t_room *room)
{
	t_lst	*elem;
	t_room	*child;

	elem = room->parents->first;
	ft_printf("\tparents: ");
	while (elem)
	{
		child = elem->content;
		ft_printf("%s (d %u, w %u) -- ", child->name, child->dist, child->walk);
		elem = elem->next;
	}
	ft_printf("\n");
	elem = room->children->first;
	ft_printf("\tchildren: ");
	while (elem)
	{
		child = elem->content;
		ft_printf("%s (%u) -- ", child->name, child->dist);
		elem = elem->next;
	}
}

int		print_room_elem(t_h_elem *room_h_elem)
{
	t_room	*room;

	room = room_h_elem->content;
	printf("PRINT ROOM ELEM FDP\n");
	print_room(room);
	return (1);
}

void	print_room(t_room *room)
{
	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING ROOM\n");
	ft_printf("room '%s': %p\n", room->name, room);
	ft_printf("\tdist %u\n", room->dist);
	ft_printf("\twalk %u\n", room->walk);
	print_relatives(room);
	ft_printf("\n");
}

void	print_lem(t_lem *lem)
{
	if (DEBUG == 0)
		return ;
	ft_printf("PRINTING LEM\n");
	ft_printf("---\nLEM\n---\n");
	ft_printf("nb_ants   : %u\n", lem->nb_ants);
	ft_printf("shortest  : %u\n", lem->shortest);
	ft_printf("max_dist  : %u\n", lem->max_dist);
}
