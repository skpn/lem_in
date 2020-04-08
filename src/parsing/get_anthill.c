/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_anthill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 13:18:41 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/07 19:04:14 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int				get_anthill(t_lem *lem)
{
	t_file		anthill_file;

	if (read_file(&anthill_file, NULL) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	lem->anthill = anthill_file.content;
	lem->anthill_size = anthill_file.size;
	if (!(lem->copy = ft_strdup(anthill_file.content)))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
