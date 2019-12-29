
#include "libft.h"

t_h_elem	*ft_hash_get_elem(t_h_table *table, char *key)
{
	unsigned	index;
	t_h_elem	*hash_elem;
	t_lst		*index_lst;

	index = table->hash_func(key) % table->size;
	index_lst = table->array[index].first;
	while (index_lst)
	{
		hash_elem = index_lst->content;
		if (!ft_strcmp(hash_elem->key, key))
			return (hash_elem);
		index_lst = index_lst->next;
	}
	return (NULL);
}

void		*ft_hash_get_content(t_h_table *table, char *key)
{
	t_h_elem	*hash_elem;

	hash_elem = ft_hash_get_elem(table, key);
	if (hash_elem)
		return (hash_elem->content);
	return (NULL);
}

t_h_elem		*ft_hash_pop_elem(t_h_table *table, char *key)
{
	unsigned	index;
	t_head		*index_head;
	t_lst		*popped_elem_lst;
	t_h_elem	*popped_elem;

	index = table->hash_func(key) % table->size;
	index_head = &(table->array[index]);
	if (index_head)
	{
		popped_elem = ft_hash_get_elem(table, key);
		popped_elem_lst = ft_lstpop(index_head, popped_elem);
		if (popped_elem_lst)
		{
			if (index_head->size > 0)
				table->collisions--;
			ft_lstfree_elem(&popped_elem_lst, FREE_LINKS);
			return (popped_elem);
		}
	}
	return (NULL);
}
