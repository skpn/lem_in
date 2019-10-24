/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:07:07 by sikpenou          #+#    #+#             */
/*   Updated: 2019/09/26 17:26:05 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	int		len1;
	int		len2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup((char *)s2));
	if (!s2)
		return (ft_strdup((char *)s1));
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	if (!(new = (char *)easymalloc(sizeof(*new) * (len1 + len2 + 1))))
		return (NULL);
	ft_strcpy(new, (char *)s1);
	ft_strcpy(new + len1, (char *)s2);
	return (new);
}
