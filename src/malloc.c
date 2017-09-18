/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:50:56 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/18 15:51:35 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*my_malloc(size_t size)
{
	void	*p;

	p = NULL;

	if ((int)size <= 0)
		return (NULL);
	else if (size < TINY_AREA)
		return alloc_tiny(size, p);
	else if (size < SMALL_AREA)
		return alloc_small(size, p);
	return alloc_large(size, p);
}

int	main(void)
{
	char *str1;
	char *str2;
	char *str3;
	char *str4;

	printf("\n\nPageSize: %d\n", getpagesize());
	str1 = (char*)my_malloc(11111);
	str2 = (char*)my_malloc(22222);
	str3 = (char*)my_malloc(33333);
	str4 = (char*)my_malloc(44444);

	printf("\nLarge\n");
	while (g_page.large)
	{
		printf("\tp: %p\n\tsize: %zu\n\n", g_page.large, g_page.large->size);
		g_page.large = g_page.large->next;
	}
	printf("Str1: %p\n", str1);
	printf("Str2: %p\n", str2);
	printf("Str3: %p\n", str3);
	printf("Str4: %p\n", str4);
	return (0);
}
