/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:56 by alngo             #+#    #+#             */
/*   Updated: 2020/03/02 12:04:56 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <limits.h>
# include <stdint.h>
# include <unistd.h>
# include <sys/mman.h>
# include <pthread.h>

# ifndef DEBUG

#  define DEBUG 0

# endif

# ifndef DHEXMEM

#  define DHEXMEM 0

# endif

# ifndef DCALLTRACE

#  define DCALLTRACE 0

# endif

typedef enum			e_malloc_flags
{
	INUSE = 0x4,
	MMAPD = 0x2,
	PREVINUSE = 0x1
}						t_malloc_flags;

typedef enum			e_malloc_type
{
	TINY = 1024,
	SMALL = 4096,
	LARGE = 4097
}						t_malloc_type;

typedef struct			s_meta
{
	size_t				size: 61;
	unsigned char		flags: 3;
	void				*next;
}						t_meta;

typedef struct			s_arena
{
	void				*tiny;
	void				*small;
	void				*large;
}						t_arena;

extern t_arena			g_arena;
extern pthread_mutex_t	g_lock;

void					*malloc(size_t size);
void					*realloc(void *ptr, size_t size);
void					free(void *ptr);

/*
** show_alloc_mem.c
*/

void					show_alloc_mem();
void					print_allocation(const char *name, void *heap,
		size_t *acc, void(*f)(void *, t_meta *));

/*
** block.c
*/

void					*get_block(void *ptr, void **heap);

/*
** fit.c
*/

void					*fit_block(void **heap, size_t size);

/*
** heap.c
*/

void					*init_heap(size_t size);
uint8_t					is_empty_heap(void *heap);
void					delete_heap(void *heap);

/*
** utils.c
*/

void					*payload(void *ptr);
t_meta					*meta(void *ptr);
t_meta					*set_meta(void *ptr, size_t size,
						unsigned char flags, void *next);
size_t					size_alignment(size_t size, size_t alignment);

/*
** mem.c
*/

void					*ft_memcpy(void *s1, const void *s2, size_t n);

/*
** out.c
*/

void					ft_putstr(const char *str);
void					ft_putnbr(size_t value, unsigned int base);
void					ft_putmem(const void *ptr, size_t n);

/*
** debug.c
*/

void					debug_block(void *payload, t_meta *data);
void					debug_output(const char *name);
void					debug_call(const char *name, size_t size, void *ptr);
void					debug_process(const char *name, int depth);

/*
** lock.c
*/

void					lock(void);
void					unlock(void);

#endif
