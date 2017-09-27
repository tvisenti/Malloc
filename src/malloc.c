/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:50:56 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/27 17:54:33 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void		*my_malloc(size_t size)
{
	void	*p;

	p = NULL;
	if ((int)size <= 0)
		return (NULL);
	else if (size < TINY_AREA)
		p = alloc_tiny(size);
	else if (size < SMALL_AREA)
		p = alloc_small(size);
	else
		p = alloc_large(size, p);
	if (p == NULL)
		return (NULL);
	return ((void*)p + BLOCK_SIZEOF);
}

int			main(void)
{
	int i = 0;
	char *addr;
	char *str = "TEST";
	while (i < 1024)
	{
		addr = (char*)my_malloc(10);
		addr[0] = 42;
		printf("p: %p\n", addr);
		my_free(str);
		i++;
	}

	return (0);
	// char	*large1;
	// char	*large2;
	// char	*large3;
	//
	// char	*small1;
	// char	*small2;
	// char	*small3;
	//
	// char	*tiny1;
	// char	*tiny2;
	// char	*tiny3;
	//
	// large1 = (char*)my_malloc(11111);
	// large2 = (char*)my_malloc(22222);
	// large3 = (char*)my_malloc(33333);
	//
	// small1 = (char*)my_malloc(333);
	// small2 = (char*)my_malloc(444);
	// small3 = (char*)my_malloc(555);
	//
	// tiny1 = (char*)my_malloc(1);
	// tiny2 = (char*)my_malloc(2);
	// tiny3 = (char*)my_malloc(3);
	//
	// printf("SIZEOF BLOCK: %lu\n", BLOCK_SIZEOF);
	// printf("\nLarge\n");
	// while (g_page.large)
	// {
	// 	printf("\tp: %p\n\tsize: %zu\n\n", g_page.large, g_page.large->size);
	// 	g_page.large = g_page.large->next;
	// }
	// printf("large_1: %p\n", large1);
	// printf("large_2: %p\n", large2);
	// printf("large_3: %p\n", large3);
	//
	// printf("\nSmall\n");
	// while (g_page.small)
	// {
	// 	printf("\tp: %p\n\tsize: %zu\n\n", g_page.small, g_page.small->size);
	// 	g_page.small = g_page.small->next;
	// }
	// printf("small_1: %p\n", small1);
	// printf("small_2: %p\n", small2);
	// printf("small_3: %p\n", small3);
	//
	// printf("\nTINY\n");
	// while (g_page.tiny)
	// {
	// 	printf("\tp: %p\n\tsize: %zu\n\n", g_page.tiny, g_page.tiny->size);
	// 	g_page.tiny = g_page.tiny->next;
	// }
	// printf("tiny_1: %p\n", tiny1);
	// printf("tiny_2: %p\n", tiny2);
	// printf("tiny_3: %p\n", tiny3);
	// return (0);
}
