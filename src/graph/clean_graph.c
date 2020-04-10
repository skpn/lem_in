/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_graph.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 15:45:39 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/08 11:50:59 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	kill_end_children(t_room *end, unsigned max_dist)
{
	t_lst	*child_elem;
	t_lst	*transfer;
	t_room	*child;

	child_elem = end->children->first;
	while (child_elem)
	{
		child = child_elem->content;
		child_elem = child_elem->next;
		transfer = ft_lstpop(end->children, child);
		if (child->dist <= max_dist)
			ft_lstadd(end->parents, transfer);
		else
			ft_lstfree_elem(&transfer, FREE_STRUCT);
	}
}

void	kill_dead_rooms(t_lem *lem, t_room *dead_room)
{
	t_lst		*parents_lst;
	t_lst		*popped;
	t_room		*parent;

	if (dead_room == lem->start)
		lem->start = NULL;
	if (dead_room->children->first != NULL || dead_room->parents->size > 1)
		return ;
	parents_lst = dead_room->parents->first;
	while (parents_lst)
	{
		parent = (t_room *)parents_lst->content;
		parents_lst = parents_lst->next;
		if ((popped = ft_lstpop(dead_room->parents, parent)))
			ft_lstfree_elem(&popped, FREE_STRUCT);
		if ((popped = ft_lstpop(parent->children, dead_room)))
			ft_lstfree_elem(&popped, FREE_STRUCT);
		if (parent->children->first == NULL)
			kill_dead_rooms(lem, parent);
	}
	ft_h_free_elem_by_key(lem->table, dead_room->name);
}
