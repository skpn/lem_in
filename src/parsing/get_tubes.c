/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tubes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:00:27 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/08 18:55:02 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int		add_links(t_lem *lem, char *name_1, char *name_2)
{
	t_room	*room_1;
	t_room	*room_2;

	if (!(room_1 = ft_h_get_content(lem->table, name_1)))
		return (PARSING_ERROR);
	if (!(room_2 = ft_h_get_content(lem->table, name_2)))
		return (PARSING_ERROR);
	if (room_1 == room_2)
		return (PARSING_ERROR);
	if (ft_lstfind(room_1->children, room_2))
		return (EXIT_SUCCESS);
	if (!ft_lstadd_new(room_1->children, room_2))
		return (ERR_MALLOC);
	if (!ft_lstadd_new(room_2->children, room_1))
		return (ERR_MALLOC);
	lem->nb_tubes++;
	return (EXIT_SUCCESS);
}

static int		get_link_names(t_lem *lem, char **name_1, char **name_2)
{
	*name_1 = lem->copy + lem->pos;
	if (!ft_strcmp(*name_1, "\n") || lem->pos >= lem->anthill_size)
		return (CONTINUE);
	while (lem->copy[lem->pos] && lem->copy[lem->pos] != '-')
		lem->pos++;
	if (lem->copy[lem->pos] != '-')
		return (PARSING_ERROR);
	lem->copy[lem->pos++] = 0;
	*name_2 = lem->copy + lem->pos;
	while (lem->copy[lem->pos] && lem->copy[lem->pos] != '\n')
		lem->pos++;
	if (lem->copy[lem->pos] != '\n')
		return (PARSING_ERROR);
	lem->copy[lem->pos++] = 0;
	return (EXIT_SUCCESS);
}

int				get_tubes(t_lem *lem, char *anthill_copy)
{
	int		start_end;
	int		ret;
	char	*name_1;
	char	*name_2;

	start_end = REJECT_START_END;
	while (anthill_copy[lem->pos] == '#')
		manage_com(lem, anthill_copy, &start_end);
	if ((ret = get_link_names(lem, &name_1, &name_2)) != EXIT_SUCCESS)
		return (ret);
	if ((ret = add_links(lem, name_1, name_2)) != EXIT_SUCCESS)
		return (ret);
	if (!lem->copy[lem->pos])
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
