/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lem_structs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:15:39 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/07 16:17:50 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_lvl		*alloc_new_lvl(void)
{
	t_lvl	*lvl;

	if (!(lvl = (t_lvl *)gc_malloc(sizeof(*lvl))))
		return (NULL);
	if (!(lvl->rooms = ft_lstnew_head()))
		return (NULL);
	lvl->dist = 0;
	return (lvl);
}

t_path		*alloc_new_path(void)
{
	t_path	*path;

	if (!(path = (t_path *)gc_malloc(sizeof(*path))))
		return (NULL);
	if (!(path->rooms = ft_lstnew_head()))
		return (NULL);
	return (path);
}

t_room		*alloc_new_room(char *name)
{
	t_room	*room;

	if (!(room = (t_room *)gc_malloc(sizeof(*room))))
		return (NULL);
	if (!(room->parents = ft_lstnew_head()))
		return (NULL);
	if (!(room->children = ft_lstnew_head()))
		return (NULL);
	room->dist = 0xFFFFFFFF;
	room->name = name;
	return (room);
}

t_config	*alloc_new_config(void)
{
	t_config	*config;

	if (!(config = (t_config *)gc_malloc(sizeof(*config))))
		return (NULL);
	if (!(config->paths = ft_lstnew_head()))
		return (NULL);
	config->turns = 0xFFFFFFFF;
	return (config);
}

int			init_lem(t_lem *lem)
{
	ft_memset(lem, 0, sizeof(*lem));
	if (!(lem->paths = ft_lstnew_head()))
		return (EXIT_FAILURE);
	if (!(lem->generic_path = alloc_new_path()))
		return (EXIT_FAILURE);
	if (!(lem->table = ft_h_alloc_new_table()))
		return (EXIT_FAILURE);
	if (ft_h_init_table(lem->table) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	lem->table->func_free = &free_table_room;
	lem->shortest = 0xFFFFFFFF;
	lem->max_dist = 0xFFFFFFFF;
	lem->turns = 0xFFFFFFFF;
	return (EXIT_SUCCESS);
}
