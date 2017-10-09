/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 15:06:43 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/09 16:56:19 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

/*
** calloc fait un malloc de count * size et un bzero sur la zone alloué
*/

void		*calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (p != NULL)
		ft_bzero(p, count * size);
	return (p);
}

/*
** reallocf fait un realloc et free le pointeur qu'on nous passe
*/

void		*reallocf(void *ptr, size_t size)
{
	void	*p;

	p = realloc(ptr, size);
	if (ptr != p || p == NULL)
	{
		free(ptr);
	}
	return (p);
}
