/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_block.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:17:25 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/18 14:29:46 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

t_block *firstBlock(size_t size)
{
	t_block *new;

	new = mmap(0, size + sizeof(t_block), PROT, MAP, -1, 0);
	new->size = size;
	new->isFree = 0;
	new->next = NULL;

	return new;
}

t_block *addLastBlock(t_block *prev, size_t size)
{
	t_block *new;

	new = mmap(0, size + sizeof(t_block), PROT, MAP, -1, 0);
	new->size = size;
	new->isFree = 0;
	new->next = NULL;
	prev->next = new;
	return (new);
}

t_block	*getLastBlock(t_block *cur)
{
	t_block *tmp;

	tmp = cur;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	return (tmp);
}

t_block	*addBlock(size_t size)
{
	t_block	*new;

	printf("Creation block\n");
	new = mmap(0, TINY_SIZE, PROT, MAP, -1, 0);
	new->size = size;
	new->isFree = 1;
	new->next = NULL;
	return (new);
}
