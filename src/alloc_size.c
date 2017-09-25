/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:21:18 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/25 18:17:58 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void		*alloc_tiny(size_t size, void *p)
{
	if (!g_page.tiny)
	{
		printf("J'existe pas encore\n");
	}
	else if (g_page.tiny && g_page.tiny->size <= size)
	{
		printf("Test\n");
	}
	return (p);
}

t_block		*create_new(t_block *old, size_t size, int is_tiny)
{
	t_block	*new;

	new = old + size + BLOCK_SIZEOF;
	old->size -= size + BLOCK_SIZEOF;
	new->size = size;
	new->isFree = 0;
	if (is_tiny == 0)
	{
		new->next = g_page.small;
		g_page.small = new;
	}
	else
	{
		new->next = g_page.tiny;
		g_page.tiny = new;
	}
	printf("new: %p\n\n", new);
	return (new);
}

t_block		*find_free_block_small(size_t size)
{
	t_block *tmp;

	tmp = g_page.small;
	while (tmp)
	{
		if (tmp->isFree == 1 && tmp->size > size)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_block		*init_new_block_small(size_t size)
{
	t_block	*tmp;

	if (!(tmp = mmap(0, SMALL_SIZE + BLOCK_SIZEOF + PAGE_SIZEOF,
		PROT, MAP, -1, 0)))
		return (NULL);
	tmp += BLOCK_SIZEOF + PAGE_SIZEOF;
	tmp->size = SMALL_SIZE - size;
	tmp->isFree = 1;
	if (!g_page.small)
		tmp->next = NULL;
	else
		tmp->next = g_page.small;
	g_page.small = tmp;
	return (tmp);
}

void		*alloc_small(size_t size, void *p)
{
	t_block *tmp;

	tmp = NULL;
	if (!g_page.small)
	{
		if (init_new_block_small(size) == NULL)
			return (NULL);
		return (create_new(g_page.small, size, 0));
	}
	else
	{
		if ((tmp = find_free_block_small(size)) == NULL)
		{
			if ((tmp = init_new_block_small(size)) == NULL)
				return (NULL);
		}
		return (create_new(tmp, size, 0));
	}
	return (p);
}

void		*alloc_large(size_t size, void *p)
{
	t_block	*tmp;
	t_block	*save;
	t_block	*new_block;

	tmp = g_page.large;
	save = tmp;
	if (!tmp)
	{
		new_block = first_block(size);
		g_page.large = new_block;
		p = new_block;
		return (p);
	}
	tmp = get_last_block(tmp);
	new_block = add_last_block(tmp, size);
	tmp->next = new_block;
	g_page.large = save;
	p = new_block;
	return (p);
}
