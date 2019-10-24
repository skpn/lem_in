/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_ptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:04:30 by sikpenou          #+#    #+#             */
/*   Updated: 2019/04/22 11:07:10 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_free_ptr(void **ptr)
{
	if (!*ptr)
		return (0);
	ft_free((void **)ptr);
	*ptr = NULL;
	return (0);
}
