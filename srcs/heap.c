/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:33:28 by alngo             #+#    #+#             */
/*   Updated: 2020/02/25 10:27:30 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*init_heap(size_t size)
{
	int		pagesize;
	int		offset;
	size_t	heap_size;
	void	*ptr;

	ptr = NULL;
	pagesize = getpagesize();
	offset = sizeof(t_meta);
	if (DCALLTRACE >= 2)
		debug_process("init_heap", 2);
	if (size <= TINY)
		heap_size = size_alignment(offset + ((TINY + offset) * 100), pagesize);
	else if (size <= SMALL)
		heap_size = size_alignment(offset + ((SMALL + offset) * 100), pagesize);
	else
		heap_size = size_alignment(offset + size, 16);
	if ((ptr = mmap(NULL, heap_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	set_meta(ptr, heap_size - offset, MMAPD, NULL);
	return (ptr);
}

void		*get_heap_surrounding(void *start, void *heap,
		void **prec, void **next)
{
	void	*page;

	page = start;
	*prec = NULL;
	*next = NULL;
	while (page)
	{
		*next = meta(page)->next;
		if (page == heap)
			return (page);
		*prec = page;
		page = *next;
	}
	return (NULL);
}

uint8_t		is_empty_heap(void *payload)
{
	void	*block;

	block = payload;
	while (block)
	{
		if (meta(block)->flags == MMAPD)
			return (1);
		if (meta(block)->flags & INUSE)
			return (0);
		block = meta(block)->next;
	}
	return (1);
}

void		delete_heap(void *heap)
{
	void	*prec;
	void	*next;
	void	*target;

	prec = NULL;
	next = NULL;
	target = NULL;
	if ((target = get_heap_surrounding(g_arena.tiny, heap, &prec, &next)))
	{
		if (!prec)
			g_arena.tiny = next;
	}
	else if ((target = get_heap_surrounding(g_arena.small, heap, &prec, &next)))
	{
		if (!prec)
			g_arena.small = next;
	}
	else if ((target = get_heap_surrounding(g_arena.large, heap, &prec, &next)))
	{
		if (!prec)
			g_arena.large = next;
	}
	if (prec)
		meta(prec)->next = next;
	munmap(target, meta(heap)->size + sizeof(t_meta));
}
