/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:18:41 by alngo             #+#    #+#             */
/*   Updated: 2020/01/28 10:34:15 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_arena		arenas = {NULL, NULL, NULL};

size_t		get_heap_size(size_t size)
{
	int		pagesize;
	int		offset;

	pagesize = getpagesize();
	offset = sizeof(t_meta);
	if (size < TINY)
		return (size_alignment(offset + ((TINY + offset) * 100), pagesize));
	else if (size < SMALL)
		return (size_alignment(offset + ((SMALL + offset) * 100), pagesize));
	return (offset + size);
}

void		*init_heap(size_t size)
{
	size_t	heap_size;
	void	*ptr;

	ptr = NULL;
	heap_size = get_heap_size(size);
	if ((ptr = mmap(ptr, heap_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	set_meta(ptr, heap_size, MMAPD, NULL);
	return (ptr);
}

void		*first_fit(void *heap, size_t size)
{
	void	*blocks;
	t_meta	*meta;

	blocks = get_payload(heap);
	meta = get_meta(blocks);
	if (!(meta->data & INUSE))
		set_meta((void *)meta, size, INUSE, NULL);
	return ((void *)meta);
}

void		*get_chunk(void **heap, size_t size)
{
	void	*block;

	(void)block;
	if (!*heap && !(*heap = init_heap(size)))
		return (NULL);
	if ((block = first_fit(*heap, size)))
		return (block);
	return (get_chunk(&((t_meta *)(*heap))->next, size));
}

void 		*malloc(size_t size)
{
	void	*block;

	if (size <= 0 || size > (~(size_t)0 >> 3))
		return (NULL);
	if (size < TINY)
		block = get_chunk(&arenas.tiny, size);
	else if (size < SMALL)
		block = get_chunk(&arenas.small, size);
	else
		return (get_chunk(&arenas.large, size));
	if (block)
		return (get_payload(block));
	return (NULL);
}
