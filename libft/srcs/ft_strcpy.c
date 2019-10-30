/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 00:17:35 by sikpenou          #+#    #+#             */
/*   Updated: 2019/10/29 14:30:04 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
char	*ft_strcpy(char *dst, char *src)
{
	long	*long_src;
	long	*long_dst;
	char	*end;

	long_src = (long *)src;
	long_dst = (long *)dst;
	while (!(!(char)(*long_src) || !(char)(*long_src >> 8)
		|| !(char)(*long_src >> 16) || !(char)(*long_src >> 24)
		|| !(char)(*long_src >> 32) || !(char)(*long_src >> 40)
		|| !(char)(*long_src >> 48) || !(char)(*long_src >> 56)))
		*long_dst++ = *long_src++;
	end = (char *)long_dst;
	src = (char *)long_src;
	while (*src)
		*end++ = *src++;
	*end = *src;
	return (dst);
}
