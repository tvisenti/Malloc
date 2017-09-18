/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:21:18 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/18 16:56:18 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*alloc_tiny(size_t size, void *p)
{
	if (!g_page.tiny)
	{
		printf("J'existe pas encore\n");
		g_page.tiny = addBlock(size);
	}
	else if (g_page.tiny && g_page.tiny->size <= size)
	{
		printf("Test\n");
	}
	return p;
}

if (!g_page.tiny && !g_page.small)
{
	g_page.tiny = mmap(0, TINY_SIZE + sizeof(t_block), PROT, MAP, -1, 0);
	g_page.small = mmap(0, SMALL_SIZE + sizeof(t_block), PROT, MAP, -1, 0);
}

void	*alloc_small(size_t size, void *p)
{
	t_block	*new;

	new = NULL;
	if (!g_page.small)
	{
		g_page.small = mmap(0, SMALL_SIZE + sizeof(t_block), PROT, MAP, -1, 0);
		
	}
	else
	{
		g_page.small = mmap(0, SMALL_SIZE + sizeof(t_block), PROT, MAP, -1, 0);
	}
	p = mmap(0, size + 1, PROT, MAP, -1, 0);
	return p;
}

void	*alloc_large(size_t size, void *p)
{
	t_block	*tmp;
	t_block	*save;
	t_block	*newBlock;

	tmp = g_page.large;
	save = tmp;
	if (!tmp)
	{
		newBlock = firstBlock(size);
		g_page.large = newBlock;
		p = newBlock;
		return (p);
	}
	tmp = getLastBlock(tmp);
	newBlock = addLastBlock(tmp, size);
	tmp->next = newBlock;
	g_page.large = save;
	p = newBlock;
	return (p);
}
