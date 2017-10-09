/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <tvisenti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/14 10:51:23 by tvisenti          #+#    #+#             */
/*   Updated: 2017/10/09 17:53:27 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include "../libft/inc/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/mman.h>
# include <unistd.h>

# define TINY_SIZE getpagesize() * 64
# define TINY_AREA 2048

# define SMALL_SIZE getpagesize() * 256
# define SMALL_AREA 8192

# define PROT PROT_READ | PROT_WRITE
# define MAP MAP_ANON | MAP_PRIVATE

# define BLOCK_SIZEOF sizeof(t_block)
# define PAGE_SIZEOF sizeof(t_page)
# define SIZE_T_MAX ((size_t)-1 - getpagesize() * 2)

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
** BONUS
*/

void				*calloc(size_t count, size_t size);
void				*reallocf(void *ptr, size_t size);

/*
** DISPLAY
*/

void				display_p(void *p);
void				display_p_and_p(void *p1, void *p2, size_t size);
void				display_str_and_p(char *str, void *p);
size_t				show_alloc_page(t_block *cur, char *zone);
void				show_alloc_mem(void);

/*
** REALLOC
*/

t_block				*find_cur_block(t_block *cur, void *ptr);
t_block				*find_page_block(void *ptr);
void				*realloc_copy_free(t_block *prev, void *ptr, size_t size);
void				*realloc(void *ptr, size_t size);

/*
** FREE
*/

void				set_ptr_free(t_block *prev, t_block *cur, void *ptr);
void				concat_free_next(t_block *prev, t_block *cur, void *ptr);
void				munmap_page_large(t_block *prev, t_block *freed, void *ptr);
void				munmap_page_small(t_block *page, size_t size,
					t_block *prev);
void				free(void *ptr);

/*
** ALLOC_SIZE
*/

void				*alloc_tiny(size_t size);
void				*alloc_small(size_t size);
void				*alloc_large(size_t size, void *p);

/*
** UTILS
*/

t_block				*find_prev_block(t_block *cur, void *ptr);
t_block				*find_free_block(size_t size, int is_tiny);
t_block				*create_new(t_block *old, size_t size);
t_block				*init_new_block_small(void);
t_block				*init_new_block_tiny(void);

/*
** HANDLER_BLOCK
*/

t_block				*first_block(size_t size);
t_block				*add_last_block(t_block *prev, size_t size);
t_block				*get_last_block(t_block *cur);

/*
** MALLOC
*/

void				*malloc(size_t size);

#endif
