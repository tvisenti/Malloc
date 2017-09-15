/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:50:56 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/15 14:26:39 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*my_malloc(size_t size)
{
	void	*p;
	if (size == 0 || size > MAX_SIZE_ALLOC)
		return NULL;
	p = mmap(0, size + 1, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	return p;
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
