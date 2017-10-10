/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:50:56 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/10 10:14:49 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void		*malloc(size_t size)
{
	void	*p;

	p = NULL;
	pthread_mutex_lock(&g_malloc_lock);
	if ((int)size <= 0 || size > SIZE_T_MAX)
	{
		pthread_mutex_unlock(&g_malloc_lock);
		return (NULL);
	}
	else if (size <= TINY_AREA)
		p = alloc_tiny(size);
	else if (size <= SMALL_AREA)
		p = alloc_small(size);
	else
		p = alloc_large(size, p);
	if (p == NULL)
	{
		pthread_mutex_unlock(&g_malloc_lock);
		return (p);
	}
	pthread_mutex_unlock(&g_malloc_lock);
	return ((void*)p + BLOCK_SIZEOF);
}
