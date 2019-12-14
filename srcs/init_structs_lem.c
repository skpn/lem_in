/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs_lem.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 22:15:39 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/14 20:05:55 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_path		*alloc_new_path(void)
{
	t_path	*path;

	if (!(path = (t_path *)easymalloc(sizeof(*path))))
		return (0);
	if (!(path->rooms = ft_lstnew_head(NULL, NULL)))
		return (0);
	return (path);
}

t_room		*alloc_new_room(void)
{
	t_room	*room;

	if (!(room = (t_room *)easymalloc(sizeof(*room))))
		return (0);
	room->dist = 0xFFFFFFFF;
	if (!(room->parents = ft_lstnew_head(NULL, NULL)))
		return (0);
	if (!(room->children = ft_lstnew_head(NULL, NULL)))
		return (0);
	return (room);
}

t_config	*alloc_new_config(void)
{
	t_config	*config;

	if (!(config = (t_config *)easymalloc(sizeof(*config))))
		return (0);
	if (!(config->paths = ft_lstnew_head(NULL, NULL)))
		return (0);
	config->turns = 0xFFFFFFFF;
	return (config);
}

t_display	alloc_new_display(void)
{
	t_display	*display;

	if (!(display = (t_display *)easymalloc(sizeof(*display))))
		return (0);
	return (display);
}

int			alloc_new_lem(t_lem **lem)
{
	if (!(*lem = (t_lem *)easymalloc(sizeof(**lem))))
		return (0);
	if (!((*lem)->rooms = ft_lstnew_head(NULL, NULL)))
		return (0);
	if (!((*lem)->config_lst = ft_lstnew_head(NULL, NULL)))
		return (0);
	if (!((*lem)->paths = ft_lstnew_head(NULL, NULL)))
		return (0);
	(*lem)->max_dist = 0xFFFFFFFF;
	(*lem)->max_paths = 0xFFFFFFFF;
	(*lem)->turns = 0xFFFFFFFF;
	return (1);
}
