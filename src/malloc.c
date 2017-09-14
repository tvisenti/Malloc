/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:50:56 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/14 13:56:47 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/malloc.h"

void	*malloc(size_t size)
{
	if (size == 0 || size == NULL || size > MAX_SIZE_ALLOC)
		return NULL;
	
}

int	main(void)
{
	return (0);
}
