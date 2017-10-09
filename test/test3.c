/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:07:07 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/09 18:54:41 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/malloc.h"

#define M (1024 * 1024)

void		print_s(char *s)
{
	write(1, s, strlen(s));
}

int			main(void)
{
	char	*addr1;
	char	*addr3;

	addr1 = (char*)malloc(16*M);
	strcpy(addr1, "Bonjours\n");
	print_s(addr1);
	addr3 = (char*)realloc(addr1, 128*M);
	addr3[127*M] = 42;
	print_s(addr3);
	return (0);
}
