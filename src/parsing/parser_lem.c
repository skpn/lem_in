/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:28:02 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/08 10:04:03 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"

int		manage_start_end(t_lem *lem, char *anthill, int *opt)
{
	if (*opt == REJECT_START_END
		&& (!ft_strncmp(anthill + lem->pos, "start\n", 6)
		|| !ft_strncmp(anthill + lem->pos, "end\n", 4)))
		return (PARSING_ERROR);
	else if (!ft_strncmp(anthill + lem->pos, "start\n", 6))
	{
		if (lem->start || *(anthill + lem->pos + 6) == '#')
			return (PARSING_ERROR);
		*opt = START;
		lem->pos += 6;
	}
	else if (!ft_strncmp(anthill + lem->pos, "end\n", 4))
	{
		if (lem->end || *(anthill + lem->pos + 4) == '#')
			return (PARSING_ERROR);
		*opt = END;
		lem->pos += 4;
	}
	else
	{
		while (anthill[lem->pos] && anthill[lem->pos++] != '\n')
			;
	}
	return (EXIT_SUCCESS);
}

int		manage_com(t_lem *lem, char *anthill, int *opt)
{
	if (anthill[++lem->pos] == '#')
	{
		++lem->pos;
		return (manage_start_end(lem, anthill, opt));
	}
	while (anthill[lem->pos] && anthill[lem->pos++] != '\n')
		;
	return (EXIT_SUCCESS);
}

int		get_ants(t_lem *lem, char *anthill)
{
	int		start_end;

	if (lem->nb_ants)
		return (CONTINUE);
	start_end = REJECT_START_END;
	if (anthill[lem->pos] == '#')
		return (manage_com(lem, anthill, &start_end));
	while (anthill[lem->pos] >= '0' && anthill[lem->pos] <= '9')
		lem->nb_ants = lem->nb_ants * 10 + anthill[lem->pos++] - '0';
	if (anthill[lem->pos] != '\n' || !anthill[lem->pos++])
		return (PARSING_ERROR);
	return (CONTINUE);
}

int		parse_input(t_lem *lem)
{
	int			ret;

	if ((ret = get_anthill(lem)) != EXIT_SUCCESS)
		return (ret);
	while ((ret = get_ants(lem, lem->copy)) == EXIT_SUCCESS)
		;
	if (ret != CONTINUE)
		return (ret);
	while ((ret = get_rooms(lem, lem->copy)) == EXIT_SUCCESS)
		;
	if (ret != CONTINUE || (!lem->start) || (!lem->end))
		return (ret);
	while ((ret = get_tubes(lem, lem->copy)) == EXIT_SUCCESS)
		;
	if (ret != CONTINUE)
		return (ret);
	if (!lem->start || !lem->end)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
