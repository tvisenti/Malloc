/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:21:18 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/03 15:00:16 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void		*alloc_tiny(size_t size)
{
	t_block *tmp;

	tmp = NULL;
	if (!g_page.tiny)
	{
		if (init_new_block_tiny() == NULL)
			return (NULL);
		return (create_new(g_page.tiny, size));
	}
	else
	{
		if ((tmp = find_free_block(size, 1)) == NULL)
		{
			if ((tmp = init_new_block_tiny()) == NULL)
				return (NULL);
		}
		return (create_new(tmp, size));
	}
}

void		*alloc_small(size_t size)
{
	t_block *tmp;

	tmp = NULL;
	if (!g_page.small)
	{
		if (init_new_block_small() == NULL)
			return (NULL);
		return (create_new(g_page.small, size));
	}
	else
	{
		if ((tmp = find_free_block(size, 0)) == NULL)
		{
			if ((tmp = init_new_block_small()) == NULL)
				return (NULL);
		}
		return (create_new(tmp, size));
	}
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
