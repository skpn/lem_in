/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:52:16 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/07 16:21:17 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

void	free_lvl(t_lvl **lvl)
{
	ft_lstfree(&(*lvl)->rooms, FREE_STRUCT, LST_FREE_HEAD);
	gc_free((void **)lvl);
}

void	free_config(t_config **config)
{
	ft_lstfree(&(*config)->paths, FREE_STRUCT, LST_FREE_HEAD);
	gc_free((void **)config);
}

void	free_table_room(t_h_elem *room_h_elem)
{
	t_room	*room;

	room = room_h_elem->content;
	ft_lstfree(&room->parents, FREE_STRUCT, LST_FREE_HEAD);
	ft_lstfree(&room->children, FREE_STRUCT, LST_FREE_HEAD);
	gc_free((void **)&room);
}

void	free_display(t_display **display)
{
	unsigned	cell;

	cell = 0;
	if ((*display)->ants_tab)
	{
		while (cell < (*display)->total_rooms)
		{
			if ((*display)->ants_tab[cell])
			{
				gc_free((void **)&((*display)->ants_tab[cell]));
			}
			cell++;
		}
		gc_free((void **)&(*display)->ants_tab);
	}
	gc_free((void **)display);
}

int		exit_lem(t_lem *lem, int ret)
{
	if (lem->table)
		ft_h_free_table(lem->table);
	if (lem->anthill)
		gc_free((void **)&lem->anthill);
	if (lem->copy)
		gc_free((void **)&lem->copy);
	if (lem->generic_path)
		free_path(&lem->generic_path);
	if (lem->paths)
		free_paths(&lem->paths);
	if (lem->best_config)
		free_config(&lem->best_config);
	if (lem->final_config)
		free_config(&lem->final_config);
	if (lem->current_config)
		free_config(&lem->current_config);
	if (lem->display)
		free_display(&lem->display);
	ft_memset(lem, 0, sizeof(*lem));
	if (ret != EXIT_SUCCESS)
		write(2, "ERROR\n", 6);
	return (ret);
}
