/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:50:56 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/04 17:08:53 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

size_t		show_alloc_page(t_block *cur, char *zone)
{
	t_block	*tmp;
	size_t	count;

	count = 0;
	tmp = cur;
	if (tmp != NULL)
		ft_printf("%s : %p\n", zone, tmp);
	else
	{
		ft_printf("%s : No zone\n", zone);
		return (0);
	}
	while (tmp)
	{
		if (tmp->is_free == 0)
		{
			ft_printf("%p - %p : %zu octets\n", (tmp + BLOCK_SIZEOF),
			(tmp + tmp->size + BLOCK_SIZEOF), tmp->size);
			count += tmp->size;
		}
		tmp = tmp->next;
	}
	return (count);
}

void		show_alloc_mem(void)
{
	size_t	count;

	count = 0;
	count += show_alloc_page(g_page.tiny, "TINY");
	count += show_alloc_page(g_page.small, "SMALL");
	count += show_alloc_page(g_page.large, "LARGE");
	ft_printf("Total: %zu\n", count);
}

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
