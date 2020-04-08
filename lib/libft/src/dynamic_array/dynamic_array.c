/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 10:44:44 by sikpenou          #+#    #+#             */
/*   Updated: 2020/04/04 11:00:07 by skpn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_d_array_free(t_d_array **d_array)
{
	unsigned	line;

	line = (*d_array)->parent_size;
	while (line)
	{
		line--;
		gc_free((*d_array)->parent_array[line]);
	}
	gc_free(*(*d_array)->parent_array);
	gc_free((void **)d_array);
}

static int	alloc_new_line(t_d_array *d_array)
{
	void		*old_array;

	if (d_array->parent_size + 2 < d_array->parent_size)
		return (ERROR_D_ARRAY_SIZE);
	old_array = d_array->parent_array;
	d_array->parent_array = gc_malloc(sizeof(void *) * ++d_array->parent_size);
	if (!(d_array->parent_array))
	{
		gc_free((void **)&d_array);
		return (ERROR_MALLOC);
	}
	if (old_array)
	{
		ft_memcpy(d_array->parent_array, old_array
			, d_array->parent_size - sizeof(void *));
		gc_free(&old_array);
	}
	d_array->parent_array[d_array->parent_size - 1] = gc_malloc(sizeof(void *)
		* D_ARRAY_LINE_SIZE);
	if (!d_array->parent_array[d_array->parent_size - 1])
		return (ERROR_MALLOC);
	d_array->pos = 0;
	return (EXIT_SUCCESS);
}

/*
** void		*ft_d_array_get_by_content(t_d_array *d_array, void *content)
** {
** 	unsigned	col;
** 	unsigned	line;
**
** 	line = d_array->parent_size;
** 	while (line)
** 	{
** 		line--;
** 		col = D_ARRAY_LINE_SIZE;
** 		while (col)
** 		{
** 			col--;
** 			if (d_array->parent_array[line][col] == content)
** 				return (d_array->parent_array[line][col]);
** 		}
** 	}
** 	return (NULL);
** }
*/

void		*ft_d_array_get_by_index(t_d_array *d_array, unsigned index)
{
	if (index / D_ARRAY_LINE_SIZE >= d_array->parent_size)
		return (NULL);
	else
		return (d_array->parent_array[index
			/ D_ARRAY_LINE_SIZE][index % D_ARRAY_LINE_SIZE]);
}

unsigned	ft_d_array_add(t_d_array *d_array, void *content)
{
	if (d_array->pos == D_ARRAY_LINE_SIZE)
	{
		if (!alloc_new_line(d_array))
			return (ERROR_MALLOC);
	}
	d_array->parent_array[d_array->parent_size - 1][d_array->pos] = content;
	d_array->pos++;
	return (D_ARRAY_LINE_SIZE * d_array->parent_size + d_array->pos);
}

t_d_array	*ft_d_array_alloc(void)
{
	t_d_array	*d_array;

	d_array = (t_d_array *)gc_malloc(sizeof(*d_array));
	if (!(d_array))
		return (NULL);
	if (alloc_new_line(d_array) != EXIT_SUCCESS)
		return (NULL);
	return (d_array);
}
