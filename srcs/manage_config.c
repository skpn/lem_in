/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:27:02 by sikpenou          #+#    #+#             */
/*   Updated: 2020/01/03 14:09:33 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

void	pop_dead_paths(t_config *config)
{
	t_lst	*path_lst;
	t_lst	*dead_path_lst;
	t_path	*path;

	path_lst = config->paths->first;
	while (path_lst)
	{
		path = path_lst->content;
		path_lst = path_lst->next;
		if (path->is_dead)
		{
			dead_path_lst = ft_lstpop(config->paths, path);
			if (dead_path_lst)
				ft_lstfree_elem(&dead_path_lst, FREE_LINKS);
		}
	}
}

int		add_path(t_lem *lem, t_path *new_path)
{
	t_lst		*config_path_lst;
	t_lst		*new_path_lst;
	unsigned	new_path_size;

	lem->lives--;
	new_path_size = new_path->rooms->size;
	if (!(new_path_lst = ft_lstnew_elem(new_path)))
		return (0);
	config_path_lst = lem->current_config->paths->first;
	if (!config_path_lst
		|| ((t_path *)config_path_lst->content)->rooms->size < new_path_size)
		ft_lstadd(lem->current_config->paths, new_path_lst);
	else
	{
		while (config_path_lst->next
			&& ((t_path *)config_path_lst->next->content)->rooms->size
				> new_path_size)
			config_path_lst = config_path_lst->next;
		ft_lstinsert(lem->current_config->paths, config_path_lst, new_path_lst
			, AFTER);
	}
	pop_dead_paths(lem->current_config);
	balance_load(lem);
	return (1);
}

int		manage_valid_path(t_lem *lem, t_path *path)
{
	if (!ft_lstadd_new(lem->paths, path))
		return (0);
	if (!add_path(lem, path))
		return (0);
	if (lem->best_config->turns <= lem->current_config->turns)
		return (1);
	if (!update_best_config(lem))
		return (0);
	return (1);
}
