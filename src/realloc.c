/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 09:31:07 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/10 10:27:38 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"
#include "../libft/inc/libft.h"
#include <stdio.h>

t_block		*find_cur_block(t_block *cur, void *ptr)
{
	t_block	*new;

	new = find_prev_block(cur, ptr);
	if ((void*)new + BLOCK_SIZEOF == ptr)
		return (new);
	if (new && new->next != NULL && new->next->is_free == 0)
		return (new->next);
	return (new);
}

t_block		*find_page_block(void *ptr)
{
	t_block	*cur;

	cur = NULL;
	if ((cur = find_cur_block(g_page.tiny, ptr)) != NULL)
		return (cur);
	else if ((cur = find_cur_block(g_page.small, ptr)) != NULL)
		return (cur);
	else if ((cur = find_cur_block(g_page.large, ptr)) != NULL)
		return (cur);
	return (cur);
}

void		*realloc_copy_free(t_block *prev, void *ptr, size_t size)
{
	void	*new;
	size_t	to_copy;
	t_block *block;

	new = malloc(size);
	block = find_page_block(new);
	if (prev == NULL)
		return (ptr);
	to_copy = size < prev->size ? size : prev->size;
	block = (void*)new - BLOCK_SIZEOF;
	ft_memcpy(new, (void*)prev + BLOCK_SIZEOF, to_copy);
	free((void*)prev + BLOCK_SIZEOF);
	return (new);
}

void		*realloc(void *ptr, size_t size)
{
	t_block	*block;

	block = NULL;
	if ((int)size < 0 || size > SIZE_T_MAX)
		return (ptr);
	pthread_mutex_lock(&g_malloc_lock);
	if (ptr == NULL)
	{
		pthread_mutex_unlock(&g_malloc_lock);
		return (malloc(size));
	}
	if ((block = find_page_block(ptr)) != NULL)
	{
		pthread_mutex_unlock(&g_malloc_lock);
		return (realloc_copy_free(block, ptr, size));
	}
	pthread_mutex_unlock(&g_malloc_lock);
	return (NULL);
}
