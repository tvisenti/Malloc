/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:50:56 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/09 15:03:12 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void		*malloc(size_t size)
{
	void	*p;

	p = NULL;
	if ((int)size <= 0 || size > SIZE_T_MAX)
		return (NULL);
	else if (size <= TINY_AREA)
		p = alloc_tiny(size);
	else if (size <= SMALL_AREA)
		p = alloc_small(size);
	else
		p = alloc_large(size, p);
	if (p == NULL)
		return (p);
	return ((void*)p + BLOCK_SIZEOF);
}
