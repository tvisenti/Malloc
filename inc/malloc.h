/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:51:23 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/14 16:19:53 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>

#define MAX_SIZE_ALLOC 10000000000

#define TINY_SIZE 992
#define TINY_AREA 16

#define SMALL_SIZE 126999
#define SMALL_AREA 512

#define LARGE_SIZE 127000


void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();
