/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:51:23 by tvisenti          #+#    #+#             */
/*   Updated: 2017/09/27 18:28:28 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/inc/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

# define debug(str, x, y) printf("%s: P = %p, size = %zu\n", str, x, y)

# define MAX_SIZE_ALLOC 10000000000

# define TINY_SIZE getpagesize() * 16 //n
# define TINY_AREA 256 // N

# define SMALL_SIZE getpagesize() * 128 // m
# define SMALL_AREA 4096 // M

# define PROT PROT_READ | PROT_WRITE
# define MAP MAP_ANON | MAP_PRIVATE

# define BLOCK_SIZEOF sizeof(t_block)
# define PAGE_SIZEOF sizeof(t_page)

typedef struct		s_block
{
	size_t			size;
	int				is_free;
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

void		*alloc_tiny(size_t size);
void		*alloc_small(size_t size);
void		*alloc_large(size_t size, void *p);

/*
** INIT_BLOCK
*/

t_block		*find_free_block(size_t size, int is_tiny);
t_block		*create_new(t_block *old, size_t size);
t_block		*init_new_block_small();
t_block		*init_new_block_tiny();

/*
** HANDLER_BLOCK
*/

t_block		*first_block(size_t size);
t_block		*add_last_block(t_block *prev, size_t size);
t_block		*get_last_block(t_block *cur);

/*
** MALLOC
*/

void		my_free(void *ptr);
void		*my_malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		show_alloc_mem();
