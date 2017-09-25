/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:51:23 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/25 15:28:49 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

#define MAX_SIZE_ALLOC 10000000000

#define TINY_SIZE getpagesize() * 2 //n
#define TINY_AREA 256 // N

#define SMALL_SIZE getpagesize() * 10 // m
#define SMALL_AREA 4096 // M

#define PROT PROT_READ | PROT_WRITE
#define MAP MAP_ANON | MAP_PRIVATE

#define BLOCK_SIZEOF sizeof(t_block)
#define PAGE_SIZEOF sizeof(t_page)

typedef struct		s_block
{
	// void			*mem;
	size_t			size;
	int				isFree;
	struct s_block	*next;
}					t_block;

typedef struct		s_page
{
	struct s_block	*tiny;
	struct s_block	*small;
	struct s_block	*large;
}					t_page;

t_page				g_page;

/*
** ALLOC_SIZE
*/

void	*alloc_tiny(size_t size, void *p);
void	*alloc_small(size_t size, void *p);
void	*alloc_large(size_t size, void *p);

/*
** HANDLER_BLOCK
*/

t_block *first_block(size_t size);
t_block *add_last_block(t_block *prev, size_t size);
t_block	*get_last_block(t_block *cur);

/*
** MALLOC
*/

void	free(void *ptr);
void	*my_malloc(size_t size);
void	*realloc(void *ptr, size_t size);
void	show_alloc_mem();
