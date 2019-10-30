/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 17:05:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/29 14:33:56 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

t_room	*new_room(t_lst *parents, t_lst *children)
{
	t_room	*room;

	if (!(room = (t_room *)malloc(sizeof(*room))))
		return (0);
	ft_memset(room, 0, sizeof(*room));
	room->parents = parents;
	room->children = children;
	return (room);
}

int		init_lem_struct(t_lem **lem)
{
	if (!(*lem = (t_lem *)malloc(sizeof(**lem))))
		return (0);
	ft_memset(*lem, 0, sizeof(**lem));
	return (1);
}

int		main(void)
{
	t_lem	*lem;

	if (!(init_lem_struct(&lem)))
		return (exit_lem(lem, "init failed\n", 1));
	if (!parse_input(lem))
		return (exit_lem(lem, "ERROR", 2));
	return (0);
}
