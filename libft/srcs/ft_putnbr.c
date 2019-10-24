/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:57:02 by sikpenou          #+#    #+#             */
/*   Updated: 2019/04/06 21:14:27 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n)
{
	long int	new;

	if (n < 0)
		ft_putchar('-');
	new = n < 0 ? -n : n;
	new = n == -2147483648 ? 2147483648 : new;
	if (new >= 10)
		ft_putnbr(new / 10);
	ft_putchar('0' + new % 10);
}
