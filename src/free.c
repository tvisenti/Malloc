/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 17:32:06 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/10 10:27:08 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void		set_ptr_free(t_block *prev, t_block *cur, void *ptr)
{
	if ((void*)cur + BLOCK_SIZEOF == ptr)
		cur->is_free = 1;
	else
	{
		prev->is_free = 1;
		cur->is_free = 0;
	}
}

/*
** BONUS: Fait un merge des blocks free (hors zone)
*/

void		concat_free_next(t_block *prev, t_block *cur, void *ptr)
{
	t_block	*next;

	next = cur->next ? cur->next : NULL;
	set_ptr_free(prev, cur, ptr);
	if (next == NULL)
	{
		cur->size += prev->size + BLOCK_SIZEOF;
		cur = (void*)cur - prev->size - BLOCK_SIZEOF;
		cur->is_free = 1;
	}
	if (next && next->is_free == 1 &&
	(((void*)cur + cur->size + BLOCK_SIZEOF) == next) && cur->is_free == 1)
	{
		cur->size += next->size + BLOCK_SIZEOF;
		cur->next = next->next;
	}
	if (prev->is_free == 1 &&
		(((void*)prev + prev->size + BLOCK_SIZEOF) == cur) && cur->is_free == 1)
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

void		munmap_page_large(t_block *prev, t_block *freed, void *ptr)
{
	if (freed == NULL)
	{
		munmap(prev, prev->size);
		g_page.large = NULL;
	}
	else if (ptr == freed)
	{
		prev->next = freed->next;
		munmap(freed, freed->size);
	}
	else
	{
		munmap(prev, prev->size);
		g_page.large = freed;
	}
}

void		free(void *ptr)
{
	t_block	*free_ptr;

	free_ptr = NULL;
	if (ptr == NULL)
		return ;
	pthread_mutex_lock(&g_malloc_lock);
	if ((free_ptr = find_prev_block(g_page.tiny, ptr)) != NULL)
	{
		concat_free_next(free_ptr, free_ptr->next, ptr);
		munmap_page_small(g_page.tiny, TINY_SIZE, free_ptr);
	}
	else if ((free_ptr = find_prev_block(g_page.small, ptr)) != NULL)
	{
		concat_free_next(free_ptr, free_ptr->next, ptr);
		munmap_page_small(g_page.small, SMALL_SIZE, free_ptr);
	}
	else if ((free_ptr = find_prev_block(g_page.large, ptr)) != NULL)
		munmap_page_large(free_ptr, free_ptr->next, ptr);
	pthread_mutex_unlock(&g_malloc_lock);
	return ;
}
