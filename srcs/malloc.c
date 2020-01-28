/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:18:41 by alngo             #+#    #+#             */
/*   Updated: 2020/01/28 12:53:48 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_arena		arenas = {NULL, NULL, NULL};

void		*first_fit(void *heap, size_t size)
{
	t_meta	*heap_meta;
	t_meta	*block_meta;
	void	*block;
	size_t	aligned_size;

	block = get_payload(heap);
	heap_meta = get_meta(heap);
	block_meta = get_meta(block);
	if (!(block_meta->flags & INUSE))
	{
		if (block_meta->size == 0 || block_meta->size > size)
		{
			aligned_size = size_alignment(size, sizeof(void *));
			set_meta((void *)block_meta, size, INUSE, block_meta + size);
		}
	}
	return (block);
}

void		*get_block(void **heap, size_t size)
{
	void	*block;

	if (!*heap && !(*heap = init_heap(size)))
		return (NULL);
	if (size > SMALL)
		return (get_payload(*heap));
	if ((block = first_fit(*heap, size)))
		return (block);
	return (get_block(&((t_meta *)(*heap))->next, size));
}

void 		*malloc(size_t size)
{
	void	*block;

	if (size <= 0 || size > (~(size_t)0 >> 3))
		return (NULL);
	if (size < TINY)
		block = get_block(&arenas.tiny, size);
	else if (size < SMALL)
		block = get_block(&arenas.small, size);
	else
		return (get_block(&arenas.large, size));
	if (block)
		return (get_payload(block));
	return (NULL);
}
