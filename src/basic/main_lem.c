/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 13:17:30 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/08 09:44:16 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"
#include <unistd.h>

int		check_enough_info(t_lem *lem)
{
	if (lem->start && lem->end)
		return (1);
	return (0);
}

int		main(void)
{
	t_lem	lem;
	int		ret;

	if (init_lem(&lem) != EXIT_SUCCESS)
		return (exit_lem(&lem, EXIT_FAILURE));
	if ((ret = parse_input(&lem)) != EXIT_SUCCESS)
		return (exit_lem(&lem, EXIT_FAILURE));
	if (!check_enough_info(&lem))
		return (exit_lem(&lem, EXIT_FAILURE));
	if (set_graph(&lem) <= 0)
		return (exit_lem(&lem, EXIT_FAILURE));
	if (lem.end->dist == 1)
		start_joined_to_end(&lem);
	else
	{
		if (!seek_paths(&lem))
			return (exit_lem(&lem, EXIT_FAILURE));
		if (!display_lem(&lem))
			return (exit_lem(&lem, EXIT_FAILURE));
	}
	exit_lem(&lem, EXIT_SUCCESS);
	return (0);
}
