/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 10:27:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/14 17:01:31 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

t_config	*copy_config(t_lem *lem)
{
	t_config	*original;
	t_config	*new_config;
	t_head		*new_head;
	
	original = lem->current_config;
	if (!(new_config = alloc_new_config(WITHOUT_HEAD)))
		return (NULL);
	if (!(new_head = ft_lstcpy(original->paths)))
		return (NULL);
	new_config->paths = new_head;
	new_config->turns = original->turns;
//	print_config(new_config);
	lem->lives = lem->end->parents->size;
	return (new_config);
}

int		replace_config(t_lem *lem, t_config *old_config)
{
	t_config	*copy;
	t_lst		*old_config_elem;

	if (!(copy = copy_config(lem)))
		return (0);
	old_config_elem = ft_lstfind(lem->config_lst, old_config);
	old_config_elem->content = lem->current_config;
	free_config(&old_config);
	return (1);
}

int		compare_configs(t_lem *lem)
{
	t_lst		*elem;
	t_config	*config;

	elem = lem->config_lst->first;
	while (elem)
	{
		config = (t_config *)elem->content;
		elem = elem->next;
		if (config->paths->size == lem->current_config->paths->size)
		{
			if (lem->current_config->turns < config->turns)
			{
//				printf("\nREPLACING CONFIG:\n");
//				print_config(config);
				if (!(replace_config(lem, config)))
				{
					PRINTPOSN;
					return (0);
				}
			}
			return (1);
		}
	}
	PRINTPOSN;
	return (0);
}

int			add_new_config(t_lem *lem, t_config *current_config)
{
	t_config	*copy;

	//printf("\nADDING CONFIG\n");
	lem->most_paths++;
	lem->turns = current_config->turns;
	if (!(copy = copy_config(lem)))
		return (0);
	if (!(ft_lstadd_new(lem->config_lst, copy)))
		return (0);
	return (1);
}

void		pop_dead_paths(t_config *config)
{
	t_lst	*path_lst;
	t_lst	*dead_path_elem;
	t_path	*path;

	path_lst = config->paths->first;
	while (path_lst)
	{
		path = path_lst->content;
		path_lst = path_lst->next;
		if (path->is_dead)
		{
			dead_path_elem = ft_lstpop(config->paths, path);
			if (dead_path_elem)
				ft_lstfree_elem(&dead_path_elem, FREE_LINKS);
		}
//		PRINTPOSN;
	}
}

// UNTESTED FUNCTION
int			add_path(t_lem *lem, t_config *config, t_path *new_path)
{
	t_lst	*config_path_elem;
	t_lst	*new_path_elem;

	lem->lives--;
	if (!(new_path_elem = ft_lstnew_elem(new_path)))
		return (0);
	if (!(config_path_elem = config->paths->first)
		|| ((t_path *)config_path_elem->content)->rooms->size > new_path->rooms->size)
		ft_lstadd(config->paths, new_path_elem);
	else
	{
		while (config_path_elem->next && ((t_path *)config_path_elem->next->content)->rooms->size > new_path->rooms->size)
			config_path_elem = config_path_elem->next;
		ft_lstinsert(config->paths, config_path_elem, new_path_elem, AFTER);
	}
	pop_dead_paths(config);
	balance_load(lem);
	return (1);
}

int			manage_valid_path(t_lem *lem, t_path *path)
{
	unsigned	current_nb_paths;
	unsigned	check_alloc;

	PRINTPOSN;
	print_path(path);
	if (!ft_lstadd_new(lem->paths, path))
		return (0);
	PRINTPOSN;
	if (!add_path(lem, lem->current_config, path))
		return (0);
	PRINTPOSN;
	current_nb_paths = lem->current_config->paths->size;
	printf("current_nb_path = %u, lem->most_paths = %u, current_config->turns = %u, lem->turns = %u\n", current_nb_paths, lem->most_paths, lem->current_config->turns, lem->turns);
	if (current_nb_paths > lem->most_paths
		&& lem->current_config->turns < lem->turns)
	{
		check_alloc = add_new_config(lem, lem->current_config);
		printf("in if, check_alloc = %d\n", check_alloc);
	}
	else
	{
		check_alloc = compare_configs(lem);
		printf("in else if, check_alloc = %d\n", check_alloc);
	}
	return (check_alloc);
}
