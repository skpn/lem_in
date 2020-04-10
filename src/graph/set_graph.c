/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_graph.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:05:19 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/08 18:56:32 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int	add_children_to_next_lvl(t_head *rooms, t_head *children)
{
	t_lst	*elem;
	t_room	*child;

	elem = children->first;
	while (elem)
	{
		child = elem->content;
		if (!child->has_lvl)
		{
			child->has_lvl = 1;
			if (!(ft_lstadd_new(rooms, child)))
				return (EXIT_FAILURE);
		}
		elem = elem->next;
	}
	return (EXIT_SUCCESS);
}

static int	get_next_lvl_rooms(t_lem *lem, t_lvl *lvl)
{
	t_lst	*current_rooms;
	t_lst	*tmp;
	t_room	*parent;

	current_rooms = lvl->rooms->first;
	ft_memset(lvl->rooms, 0, sizeof(*(lvl->rooms)));
	while (current_rooms)
	{
		parent = current_rooms->content;
		if (parent->children->first != NULL)
		{
			if (add_children_to_next_lvl(lvl->rooms, parent->children)
				!= EXIT_SUCCESS)
				return (EXIT_FAILURE);
		}
		else if (parent != lem->end)
			kill_dead_rooms(lem, parent);
		tmp = current_rooms;
		current_rooms = current_rooms->next;
		ft_lstfree_elem(&tmp, FREE_STRUCT);
	}
	return (EXIT_SUCCESS);
}

static int	set_first_lvl(t_lem *lem, t_lvl *lvl)
{
	if (!(ft_lstadd_new(lvl->rooms, lem->start)))
	{
		free_lvl(&lvl);
		return (EXIT_FAILURE);
	}
	lem->start->dist = 0;
	lem->end->has_lvl = 1;
	return (EXIT_SUCCESS);
}

static int	set_lvls(t_lem *lem, t_lvl *lvl)
{
	if (set_first_lvl(lem, lvl) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	while (lvl->dist < lem->max_dist && lvl->rooms->first)
	{
		set_next_lvl_dists(lvl);
		set_next_lvl_families(lvl, lem->end);
		if (get_next_lvl_rooms(lem, lvl) != EXIT_SUCCESS)
		{
			free_lvl(&lvl);
			return (EXIT_FAILURE);
		}
		if (lvl->dist + 1 == lem->end->dist)
		{
			lem->shortest = lvl->dist + 2;
			lem->max_dist = lem->shortest + lem->nb_ants - 1;
		}
		lvl->dist++;
	}
	return (EXIT_SUCCESS);
}

int			set_graph(t_lem *lem)
{
	t_lvl	*lvl;

	if (!(lvl = alloc_new_lvl()))
		return (EXIT_FAILURE);
	if (set_lvls(lem, lvl) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	lem->max_dist = lvl->dist;
	free_lvl(&lvl);
	if (lem->start == NULL)
		return (EXIT_FAILURE);
	if (lem->shortest != lem->end->dist + 1
		&& !ft_lstfind(lem->start->children, lem->end))
		return (PARSING_ERROR);
	kill_end_children(lem->end, lem->max_dist);
	lem->start->dist = 0;
	return (EXIT_SUCCESS);
}
