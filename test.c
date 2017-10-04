/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:07:07 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/04 15:15:42 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"

int			main(void)
{
	int		i;
	char	*addr;
	char	*str;

	str = "TEST";
	i = 0;
	while (i < 10)
	{
		addr = (char*)malloc(11);
		addr[0] = 42;
		addr = (char*)realloc(addr, 222);
		// free(addr);
		printf("addr: %p\n", addr);
		i++;
	}
	// show_alloc_mem();
	// free(str);
	return (0);
}
