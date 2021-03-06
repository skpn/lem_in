/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sikpenou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 21:08:21 by sikpenou          #+#    #+#             */
/*   Updated: 2019/04/11 15:55:30 by sikpenou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striter(char *s, void (*f)(char *))
{
	char	*cpy_s;

	if (!(cpy_s = s) || !f)
		return ;
	while (*cpy_s)
	{
		(*f)(&(*cpy_s));
		cpy_s++;
	}
}
