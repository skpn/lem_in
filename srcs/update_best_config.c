/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 14:08:55 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/06 10:41:27 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "libft.h"

static t_path	*copy_path(t_path *original_path)
{
	t_path	*new_path;

	if (!(new_path = alloc_new_path()))
		return (NULL);
	ft_lstfree_head(&new_path->rooms);
	if (!(new_path->rooms = ft_lstcpy(original_path->rooms)))
		return (NULL);
	new_path->load = original_path->load;
	return (new_path);
}

static int		copy_current_paths(t_lem *lem)
{
	t_lst		*current_paths_lst;
	t_path		*new_path;

	current_paths_lst = lem->current_config->paths->first;
	while (current_paths_lst)
	{
		if (!(new_path = copy_path(current_paths_lst->content)))
			return (0);
		current_paths_lst = current_paths_lst->next;
		if (!ft_lstadd_new(lem->best_config->paths, new_path)
			|| !ft_lstadd_new(lem->paths, new_path))
		{
			free_path(&new_path);
			return (0);
		}
	}
	return (1);
}

static void		scramble_end_parents(t_lem *lem)
{
	if (lem->end->parents->size < 2)
		return ;
	if (lem->scramble_flip == 1)
	{
		lem->scramble_flip = 0;
		ft_lstswap_contents(lem->end->parents->last
			, lem->end->parents->last->prev);
	}
	else
	{
		lem->scramble_flip = 1;
		ft_lstswap_contents(lem->end->parents->last, lem->end->parents->first);
	}
}

int				update_best_config(t_lem *lem)
{
	if (lem->best_config->paths->first)
		ft_lstfree(&lem->best_config->paths, FREE_LINKS, KEEP_HEAD);
	if (!copy_current_paths(lem))
		return (0);
	if (!lem->best_config->turns
		|| lem->best_config->turns == lem->current_config->turns)
		scramble_end_parents(lem);
	lem->best_config->turns = lem->current_config->turns;
	lem->lives = lem->max_lives;
	return (1);
}
