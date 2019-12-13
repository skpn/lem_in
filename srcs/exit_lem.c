/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:52:16 by sikpenou          #+#    #+#             */
/*   Updated: 2019/12/13 14:23:47 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "lem_in.h"

void	free_room(t_head *rooms, t_room **room)
{
	print_room(*room);
	ft_lstpop(rooms, *room);
	dprintf(g_fd, "freeing room name\n");
	ft_free((void **)&(*room)->name);
	dprintf(g_fd, "freeing room parents head\n");
	ft_lstfree(&(*room)->parents, FREE_LINKS, FREE_HEAD);
	dprintf(g_fd, "freeing room children head\n");
	ft_lstfree(&(*room)->children, FREE_LINKS, FREE_HEAD);
	dprintf(g_fd, "freeing room itself\n");
	ft_free((void **)room);
}

void	free_rooms(t_head **rooms)
{
	t_lst	*elem;
	t_lst	*tmp;

	printf("freeing head %p, first: %p, last: %p, size: %u\n"
		, *rooms, (*rooms)->first, (*rooms)->last, (*rooms)->size);
	elem = (*rooms)->first;
	while (elem)
	{
		tmp = elem->next;
		free_room(*rooms, (t_room **)&elem->content);
		dprintf(g_fd, "freeing room link\n");
		ft_lstfree_elem(&elem, FREE_LINKS);
		elem = tmp;
	}
	dprintf(g_fd, "freeing room head\n");
	ft_lstfree_head(rooms);
	printf("rooms freed ok\n");
}

void	free_path(t_path **path)
{
	ft_lstfree(&(*path)->rooms, FREE_LINKS, FREE_HEAD);
	ft_free((void **)path);
}

void	free_paths(t_head **paths)
{
	t_lst	*elem;

	elem = (*paths)->first;
	while (elem)
	{
		free_path((t_path **)&elem->content);
		elem = elem->next;
	}
	ft_lstfree_head(paths);
}

void	free_config(t_config **config)
{
	ft_lstfree(&(*config)->paths, FREE_LINKS, FREE_HEAD);
	ft_free((void **)config);
}

void	free_config_lst(t_head *config_lst)
{
	t_lst	*config_elem;

	config_elem = config_lst->first;
	while (config_elem)
	{
		free_config((t_config **)&(config_elem->content));
		config_elem = config_elem->next;
	}
	ft_lstfree(&config_lst, FREE_LINKS, FREE_HEAD);
}

int		exit_lem(t_lem *lem, char *msg, int ret)
{
	if (lem->config_lst->first)
		free_config_lst(lem->config_lst);
	if (lem->rooms)
	{
		PRINTPOSN;
		print_rooms(lem->rooms);
		free_rooms(&lem->rooms);
	}
	msg ? write(1, msg, ft_strlen(msg)) : 0;
	dprintf(g_fd, "freeing anthill\n");
	ft_free((void **)&lem->anthill);
	dprintf(g_fd, "freeing lem\n");
	ft_free((void **)&lem);
	return (ret);
}
