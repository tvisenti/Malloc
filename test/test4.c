/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:07:07 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/10 10:29:33 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void		print_s(char *s)
{
	write(1, s, strlen(s));
}

int			main(void)
{
	char	*addr;

	addr = malloc(16);
	free(NULL);
	free((void*)addr + 5);
	if (realloc((void*)addr + 5, 10) == NULL)
		print_s("Bonjours\n");
	return (0);
}
