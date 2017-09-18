/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:50:56 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/18 10:08:46 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*alloc_tiny(size_t size)
{
	void	*p;

	p = mmap(0, size + 1, PROT, MAP, -1, 0);
	return p;
}

void	*alloc_small(size_t size)
{
	void	*p;

	p = mmap(0, size + 1, PROT, MAP, -1, 0);
	return p;
}

void	*alloc_large(size_t size)
{
	void	*p;

	p = mmap(0, size + 1, PROT, MAP, -1, 0);
	return p;
}

void	*my_malloc(size_t size)
{
	if (size < 0)
		return (NULL);
	else if (size < TINY_AREA)
		return alloc_tiny(size);
	else if (size < SMALL_AREA)
		return alloc_small(size);
	return alloc_large(size);
}

int	main(void)
{
	char *str;

	printf("\n\nPageSize: %d\n", getpagesize());
	str = (char*)my_malloc(16);
	// str = "je teste caldgnnelg";
	printf("str: %p", str);
	return (0);
}
