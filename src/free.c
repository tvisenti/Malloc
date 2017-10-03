/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 17:32:06 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/03 16:58:41 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_block		*find_prev_block(t_block *cur, void *ptr)
{
	t_block	*tmp;

	tmp = cur;
	if (tmp == NULL || ptr == NULL)
		return (NULL);
	if ((void*)tmp + BLOCK_SIZEOF == ptr)
		return (tmp);
	while (tmp->next)
	{
		if (((void*)tmp->next + BLOCK_SIZEOF) == ptr)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void		concat_free_next(t_block *prev, t_block *cur)
{
	t_block	*next;

	next = cur->next ? cur->next : NULL;
	cur->is_free = 1;
	if (next == NULL)
	{
		cur->size += prev->size + BLOCK_SIZEOF;
		cur = (void*)cur - prev->size - BLOCK_SIZEOF;
		cur->is_free = 1;
	}
	if (next && next->is_free == 1 &&
	(((void*)cur + cur->size + BLOCK_SIZEOF) == next))
	{
		cur->size += next->size + BLOCK_SIZEOF;
		cur->next = next->next;
	}
	if (prev->is_free == 1 &&
		(((void*)prev + prev->size + BLOCK_SIZEOF) == cur))
	{
		prev->size += cur->size + BLOCK_SIZEOF;
		prev->next = cur->next;
	}
}

void		munmap_page_small(t_block *page, size_t size, t_block *prev)
{
	t_block	*tmp;

	tmp = page;
	if (tmp->next == NULL || prev->next == NULL)
		return ;
	while (tmp)
	{
		if (tmp->size == size)
		{
			prev->next = tmp->next;
			munmap(tmp, size);
			return ;
		}
		if (find_prev_block(page, &tmp) == NULL)
			return ;
		tmp = tmp->next;
	}
}

void		munmap_page_large(t_block *prev, t_block *freed)
{
	if (freed == NULL)
	{
		munmap(prev, prev->size);
		g_page.large = NULL;
	}
	else
	{
		prev->next = freed->next;
		munmap(freed, freed->size);
	}
}

void		my_free(void *ptr)
{
	t_block	*free_ptr;

	free_ptr = NULL;
	if ((free_ptr = find_prev_block(g_page.tiny, ptr)) != NULL)
	{
		concat_free_next(free_ptr, free_ptr->next);
		munmap_page_small(g_page.tiny, TINY_SIZE, free_ptr);
	}
	else if ((free_ptr = find_prev_block(g_page.small, ptr)) != NULL)
	{
		concat_free_next(free_ptr, free_ptr->next);
		munmap_page_small(g_page.small, SMALL_SIZE, free_ptr);
	}
	else if ((free_ptr = find_prev_block(g_page.large, ptr)) != NULL)
		munmap_page_large(free_ptr, free_ptr->next);
	return ;
}
