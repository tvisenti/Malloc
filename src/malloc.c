/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:50:56 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/25 16:19:14 by tvisenti         ###   ########.fr       */
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
		return (alloc_tiny(size, p));
	else if (size < SMALL_AREA)
		return (alloc_small(size, p));
	return (alloc_large(size, p));
}

int			main(void)
{
	char	*strlarge1;
	char	*strlarge2;
	char	*strlarge3;

	char	*strsmall1;
	char	*strsmall2;
	char	*strsmall3;

	printf("\nPageSize: %d\n\n", getpagesize());
	strlarge1 = (char*)my_malloc(11111);
	strlarge2 = (char*)my_malloc(22222);
	strlarge3 = (char*)my_malloc(33333);

	strsmall1 = (char*)my_malloc(333);
	strsmall2 = (char*)my_malloc(444);
	strsmall3 = (char*)my_malloc(555);
	
	printf("\nLarge\n");
	while (g_page.large)
	{
		printf("\tp: %p\n\tsize: %zu\n\n", g_page.large, g_page.large->size);
		g_page.large = g_page.large->next;
	}
	printf("strlarge1: %p\n", strlarge1);
	printf("strlarge2: %p\n", strlarge2);
	printf("strlarge3: %p\n", strlarge3);

	printf("\nSmall\n");
	while (g_page.small)
	{
		printf("\tp: %p\n\tsize: %zu\n\n", g_page.small, g_page.small->size);
		g_page.small = g_page.small->next;
	}
	printf("strsmall1: %p\n", strsmall1);
	printf("strsmall2: %p\n", strsmall2);
	printf("strsmall3: %p\n", strsmall3);
	return (0);
}
