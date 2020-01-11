/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 14:36:21 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/11 14:17:27 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static t_room	*check_room(t_lem *lem, t_room *child, t_room *next_room)
{
	if (!next_room)
		return (child);
	if (lem->algo_flip <= 11 && lem->algo_flip >= 6
		&& (child->walk + child->dist <= next_room->walk + next_room->dist))
		return (child);
	else if (lem->algo_flip <= 5
		&& ((child->walk << 1) + child->dist <= (next_room->walk << 1)
		+ next_room->dist))
		return (child);
	else if (lem->algo_flip >= 12
		&&	child->walk + 3 * child->dist <= next_room->walk
		+ 3 * next_room->dist)
		return (child);
	return (next_room);
}

static int		update_room(t_room *room, t_path *path)
{
	room->walk++;
	room->previous_path = room->current_path;
	if (room->previous_path)
		room->previous_path->is_dead = 1;
	room->current_path = path;
	if (!ft_lstadd_new(path->rooms, room))
		return (0);
	return (1);
}

static t_room	*get_next_room(t_lem *lem, t_path *path, t_room *room)
{
	t_room	*next_room;
	t_lst	*child_lst;
	t_room	*child;

	next_room = NULL;
	child_lst = room->parents->first;
	while (child_lst)
	{
		child = child_lst->content;
		if (child->current_path != path
			&& child->dist + path->rooms->size <= lem->current_config->turns)
		{
			next_room = check_room(lem, child, next_room);
		}
		child_lst = child_lst->next;
	}
	child_lst = room->children->first;
	while (child_lst)
	{
		child = child_lst->content;
		if (child->current_path != path
			&& child->dist + path->rooms->size <= lem->current_config->turns)
		{
			next_room = check_room(lem, child, next_room);
		}
		child_lst = child_lst->next;
	}
	return (next_room);
}

static void		erase_current_path(t_path *path)
{
	t_lst	*room_lst;
	t_room	*room;

	room_lst = path->rooms->first;
	while (room_lst)
	{
		room = room_lst->content;
		room_lst = room_lst->next;
		room->current_path = room->previous_path;
		room->previous_path = NULL;
		if (room->current_path)
			room->current_path->is_dead = 0;
//		room->is_closed = 0;
	}
}

static int		try_path(t_lem *lem, t_path **path)
{
	t_room		*room;
	unsigned	max_dist;

	max_dist = lem->best_config ? lem->best_config->turns : 0xFFFFFFFF;
	if (!(*path = alloc_new_path()))
		return (0);
	if (!ft_lstadd_new((*path)->rooms, lem->end))
		return (0);
	lem->end->current_path = *path;
	room = get_next_room(lem, *path, lem->end);
	if (!update_room(room, *path))
		return (0);
	while ((*path)->rooms->size < max_dist
		&& (room = get_next_room(lem, *path, room)))
	{
		if (!update_room(room, *path))
			return (0);
		if (room == lem->start)
		{
			lem->start->walk = 0;
			lem->start->current_path = NULL;
			lem->end->current_path = NULL;
			return (1);
		}
	}
	erase_current_path(*path);
	free_path(path);
	return (-1);
}

int				reset_room_relaunch(t_h_elem *room_h_elem)
{
	t_room *room;

	//ft_printf("RESET ROOM RELAUNCH FDP\n");
	room = room_h_elem->content;
	room->walk = 0;
	room->current_path = NULL;
	room->previous_path = NULL;
	return (1);
}

int				best_to_final(t_lem *lem)
{
	lem->final_config->turns = lem->best_config->turns;
	ft_lstfree(&lem->final_config->paths, FREE_LINKS, KEEP_HEAD);
	if (!(lem->final_config->paths = ft_lstcpy(lem->best_config->paths)))
		return (0);
	return (1);
}

int				clean_after_algo(t_lem *lem)
{
	lem->algo_flip++;
	lem->current_config->turns = 0xFFFFFFFF;
	ft_lstfree(&lem->current_config->paths, FREE_LINKS, KEEP_HEAD);
	ft_hash_iter(lem->table, &reset_room_relaunch);
	if (lem->best_config->turns < lem->final_config->turns)
	{
		if (!(best_to_final(lem)))
			return (0);
	}
	ft_lstfree(&lem->best_config->paths, FREE_LINKS, KEEP_HEAD);
	lem->best_config->turns = 0xFFFFFFFF;
//	ft_hash_iter(lem->table, &print_room_elem);
	return (1);
}

int				seek_paths(t_lem *lem)
{
	t_path		*path;
	int			check_alloc;
	
	lem->max_lives = lem->end->parents->size + lem->end->dist * lem->nb_tubes;
	if (lem->max_lives > LIVES_UPPER_LIMIT)
		lem->max_lives = LIVES_UPPER_LIMIT;
	else if (lem->max_lives < LIVES_LOWER_LIMIT)
		lem->max_lives = LIVES_LOWER_LIMIT;
	if (!(lem->current_config = alloc_new_config())
		|| !(lem->best_config = alloc_new_config())
		|| !(lem->final_config = alloc_new_config()))
		return (0);
	while (lem->algo_flip < NB_ALGO_LAUNCHS)
	{
		lem->lives = lem->max_lives;
		lem->reset_flip = 0;
		path = NULL;
		while (lem->lives)
		{
			if (!(check_alloc = try_path(lem, &path)))
				return (0);
			else if (check_alloc == 1)
			{
				if (!manage_valid_path(lem, path))
					return (0);
			}
		}
		if (!(clean_after_algo(lem)))
			return (0);
	}
	return (1);
}
