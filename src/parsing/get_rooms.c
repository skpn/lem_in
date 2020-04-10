/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rooms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 15:41:30 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/08 18:55:02 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

static int		skip_coord(t_lem *lem)
{
	if (lem->copy[lem->pos++] != '\0')
		return (PARSING_ERROR);
	while (lem->copy[lem->pos] <= '9' && lem->copy[lem->pos] >= '0')
	{
		lem->pos++;
	}
	if (lem->copy[lem->pos++] != ' ')
		return (PARSING_ERROR);
	while (lem->copy[lem->pos] <= '9' && lem->copy[lem->pos] >= '0')
	{
		lem->pos++;
	}
	if (lem->copy[lem->pos++] != '\n')
	{
		return (PARSING_ERROR);
	}
	return (EXIT_SUCCESS);
}

static int		check_same_name(t_lem *lem, char *name_to_check)
{
	if (ft_h_get_elem(lem->table, name_to_check))
		return (PARSING_ERROR);
	return (EXIT_SUCCESS);
}

static int		get_name(t_lem *lem, char **name)
{
	unsigned	start_pos;
	char		c;

	if ((c = lem->copy[lem->pos]) == 'L' || c == '-' || c == '\0' || c == ' ')
		return (PARSING_ERROR);
	start_pos = lem->pos;
	while ((c = lem->copy[++lem->pos]) != ' ')
	{
		if (c == '\0' || c == '\n')
		{
			lem->pos = start_pos;
			return (PARSING_ERROR);
		}
		else if (c == '-')
		{
			lem->pos = start_pos;
			return (CONTINUE);
		}
	}
	*name = lem->copy + start_pos;
	lem->copy[lem->pos] = 0;
	return (skip_coord(lem));
}

int				get_rooms(t_lem *lem, char *anthill_copy)
{
	int		check_start_end;
	int		ret;
	t_room	*room;
	char	*name;

	check_start_end = ACCEPT_START_END;
	while (anthill_copy[lem->pos] == '#')
	{
		if (manage_com(lem, anthill_copy, &check_start_end) != EXIT_SUCCESS)
			return (PARSING_ERROR);
	}
	if ((ret = get_name(lem, &name)) != EXIT_SUCCESS)
		return (ret);
	if (check_same_name(lem, name) != EXIT_SUCCESS)
		return (PARSING_ERROR);
	if (!(room = alloc_new_room(name)))
		return (ERR_MALLOC);
	if (ft_h_add_elem(lem->table, room->name, room) != EXIT_SUCCESS)
		return (ERR_MALLOC);
	if (check_start_end == START)
		lem->start = room;
	else if (check_start_end == END)
		lem->end = room;
	return (EXIT_SUCCESS);
}
