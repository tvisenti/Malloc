/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 17:32:06 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/28 18:16:03 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_block		*find_block_for_free(t_block *cur, void *ptr)
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

void		concat_free_next(t_block *prev, t_block *cur, t_block *next)
{
	cur->is_free = 1;
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

// (((void*)cur + cur->size + BLOCK_SIZEOF) == next))
// (((void*)prev + prev->size + BLOCK_SIZEOF) == cur))


int			free_zone_ptr(t_block *cur, t_block *free_ptr, size_t size)
{
	t_block	*tmp;

	tmp = cur;
	while (tmp)
	{
		if (tmp == free_ptr && size == free_ptr->size)
		{
			if (munmap(tmp, size) != 0)
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void		free_next_ptr(t_block *prev_free)
{
	if (free_zone_ptr(prev_free->next, g_page.tiny, TINY_SIZE))
		g_page.tiny = NULL;
	else if (free_zone_ptr(prev_free->next, g_page.small, SMALL_SIZE))
		g_page.small = NULL;
	else if (free_zone_ptr(prev_free->next, g_page.large, prev_free->next->size))
		g_page.large = NULL;
	else
		concat_free_next(prev_free, prev_free->next, prev_free->next->next);
}

void		my_free(void *ptr)
{
	t_block	*free_ptr;

	free_ptr = NULL;
	if ((free_ptr = find_block_for_free(g_page.tiny, ptr)) != NULL)
		free_next_ptr(free_ptr);
	else if ((free_ptr = find_block_for_free(g_page.small, ptr)) != NULL)
		free_next_ptr(free_ptr);
	else if ((free_ptr = find_block_for_free(g_page.large, ptr)) != NULL)
		free_next_ptr(free_ptr);
	return ;

	// t_block	*tmp;
	//
	// if ((tmp = (t_block*)ptr) == NULL)
	// {
	// 	printf("WAT\n");
	// 	return ;
	// }
	// if (tmp->size <= 0)
	// 	return ;
	// printf("ptr: %p\n", tmp);
	// printf("size: %zu\n", tmp->size);

	// free
	return ;
}
