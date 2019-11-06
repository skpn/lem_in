/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 15:28:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/11/06 13:04:02 by hehlinge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lem_in.h"
#include <stdlib.h>

char	*ft_strjoin_anthill(char **s1, char **s2, int opt)
{
	int		len1;
	int		len2;
	char	*new;
	char	*backn;

	new = NULL;
	backn = "\n";
	if (*s1 && *s2)
	{
		len1 = ft_strlen(*s1);
		len2 = ft_strlen(*s2);
		if (!(new = (char *)malloc(len1 + len2 + 2)))
			return (NULL);
		ft_strcpy(new, *s1);
		ft_strcpy(new + len1, *s2);
		*(new + len1 + len2) = '\n';
	}
	else if (*s1 || *s2)
		new = *s1 ? ft_strjoin_anthill(s1, &backn, LEFT)
			: ft_strjoin_anthill(s2, &backn, 0);
	opt == BOTH || opt == LEFT ? ft_free((void **)s1) : 0;
	opt == BOTH || opt == RIGHT ? ft_free((void **)s2) : 0;
	return (new);
}

int		parse_input(t_lem *lem)
{
	char	*line;
	int		ret;
	int		index;
	int		(*tab[3])(t_lem *, char **, int *);

	line = 0;
	tab[0] = parse_ants;
	tab[1] = parse_room;
	tab[2] = parse_tube;
	index = 0;
	while ((ret = gnl_lem_in(0, &(lem->shortest), &(lem->turns), &line) > 0))
	{
		PRINTPOSN;
		if (!(tab[index](lem, &line, &index)))
			return (-1);
		PRINTPOSN;
		printf("before join anthill line: %p, '%s'\n", line, line);
		if (!(lem->anthill = ft_strjoin_anthill(&(lem->anthill), &line, LEFT)))
			return (-1);
		printf("after join anthill line: %p, '%s'\n", line, line);
		PRINTPOSN;
	}
		PRINTPOSN;
	ft_free((void **)&line);
		PRINTPOSN;
	lem->shortest = 0xFFFFFFFF;
		PRINTPOSN;
	lem->turns = 0;
		PRINTPOSN;
	return (ret ? 0 : 1);
}
