/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:33:28 by alngo             #+#    #+#             */
/*   Updated: 2020/01/28 14:56:20 by alngo            ###   ########.fr       */
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
	if (size < TINY)
		heap_size = size_alignment(offset + ((TINY + offset) * 100), pagesize);
	else if (size < SMALL)
		heap_size = size_alignment(offset + ((SMALL + offset) * 100), pagesize);
	else
		heap_size = offset + size;
	if ((ptr = mmap(ptr, heap_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	set_meta(ptr, heap_size, MMAPD, NULL);
	return (ptr);
}

void 		*get_heap_surrounding(void *start, void *heap,
		void **prec, void **next)
{
	void 	*page;
	t_meta 	*data;

	*prec = NULL;
	page = start;
	data = get_meta(page);
	*next = data->next;
	while (page)
	{
		if (page == heap)
			return (page);
		*prec = page;
		page = data->next;
		data = get_meta(page);
		*next = data->next;
	}
	return (NULL);
}

uint8_t 	is_empty_heap(void *payload)
{
	void 	*block;
	t_meta 	*data;

	block = payload;
	data = get_meta(block);
	while (block)
	{
		if (data->flags == MMAPD)
			return (1);
		if (data->flags & INUSE)
			return (0);
		block = data->next;
		data = get_meta(block);
	}
	return (1);
}

void 		delete_heap(void *heap)
{
	void 	*prec;
	void 	*next;
	void 	*target;

	target = NULL;
	if ((target = get_heap_surrounding(&g_arena.tiny, heap, &prec, &next)))
		if (!prec)
			g_arena.tiny = NULL;
	if ((target = get_heap_surrounding(&g_arena.small, heap, &prec, &next)))
		if (!prec)
			g_arena.small = NULL;
	if ((target = get_heap_surrounding(&g_arena.large, heap, &prec, &next)))
		if (!prec)
			g_arena.large = NULL;
	if (prec)
		get_meta(prec)->next = next;
	munmap(heap, get_meta(heap)->size);
}
