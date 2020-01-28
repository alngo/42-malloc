/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:17:56 by alngo             #+#    #+#             */
/*   Updated: 2020/01/28 11:01:22 by alngo            ###   ########.fr       */
/*                                                                           */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

#include <stddef.h>
#include <limits.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>

typedef enum		e_malloc_mask
{
	FLAGS = 0x7,
	INUSE = 0x4,
	MMAPD = 0x2,
	PREVINUSE = 0x1
}					t_malloc_mask;

typedef enum		e_malloc_type
{
	TINY = 128,
	SMALL = 1024,
	LARGE = 4096
}					t_malloc_type;

typedef struct		s_meta
{
	size_t			data;
	void			*next;
}					t_meta;

typedef struct		s_arena
{
	void			*tiny;
	void			*small;
	void			*large;
}					t_arena;

t_arena				arenas;

void				*malloc(size_t size);


/*
** utils.c
*/

void		*get_payload(void *ptr);
t_meta		*get_meta(void *ptr);
t_meta		*set_meta(void *ptr, size_t size, uint8_t flags, void *next);
size_t		size_alignment(size_t size, size_t alignment);

#endif
