/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:17:25 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/26 17:43:14 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_block		*first_block(size_t size)
{
	t_block *new;

	if (!(new = mmap(0, size + BLOCK_SIZEOF, PROT, MAP, -1, 0)))
		return (NULL);
	new->size = size;
	new->is_free = 0;
	new->next = NULL;
	return (new);
}

t_block		*add_last_block(t_block *prev, size_t size)
{
	t_block *new;

	if (!(new = mmap(0, size + BLOCK_SIZEOF, PROT, MAP, -1, 0)))
		return (NULL);
	new->size = size;
	new->is_free = 0;
	new->next = NULL;
	prev->next = new;
	return (new);
}

t_block		*get_last_block(t_block *cur)
{
	t_block *tmp;

	tmp = cur;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
