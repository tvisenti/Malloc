/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:21:18 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/26 18:45:42 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_block		*find_free_block(size_t size, int is_tiny)
{
	t_block *tmp;

	if (is_tiny == 1)
		tmp = g_page.tiny;
	else
		tmp = g_page.small;
	while (tmp)
	{
		if (tmp->is_free == 1 && tmp->size > size)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

t_block		*create_new(t_block *old, size_t size)
{
	t_block	*new;

	new = old;
	old += size + BLOCK_SIZEOF;
	old->is_free = new->is_free;
	old->size = new->size - size;
	old->next = new->next;
	new->size = size;
	new->is_free = 0;
	new->next = old;
	return (new);
}

t_block		*init_new_block_tiny(size_t size)
{
	t_block	*new;

	if (!(new = mmap(0, TINY_SIZE, PROT, MAP, -1, 0)))
		return (NULL);
	new->size = TINY_SIZE - size;
	new->is_free = 1;
	if (!g_page.tiny)
		new->next = NULL;
	else
		new->next = g_page.tiny;
	g_page.tiny = new;
	return (new);
}

t_block		*init_new_block_small(size_t size)
{
	t_block	*new;

	if (!(new = mmap(0, SMALL_SIZE, PROT, MAP, -1, 0)))
		return (NULL);
	new->size = SMALL_SIZE - size;
	new->is_free = 1;
	if (!g_page.small)
		new->next = NULL;
	else
		new->next = g_page.small;
	g_page.small = new;
	return (new);
}
