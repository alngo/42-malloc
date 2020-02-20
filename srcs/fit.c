/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:28:59 by alngo             #+#    #+#             */
/*   Updated: 2020/02/20 09:56:17 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			fit_in(void *heap, void *block, size_t size)
{
	void	*ptr;
	uint8_t	fit_size;
	uint8_t	fit_in_heap;

	fit_size = 0;
	fit_in_heap = 0;

	if (meta(block)->size == 0 || meta(block)->size >= size)
		fit_size = 1;
	ptr = block + sizeof(t_meta) + size;
	if (ptr <= (heap + sizeof(t_meta) + meta(heap)->size))
		fit_in_heap = 1;
	return (fit_size && fit_in_heap);
}

void		*fit_block_large(void *heap, size_t size)
{
	if (meta(heap)->flags & INUSE)
		return (NULL);
	set_meta(heap, size, INUSE | MMAPD, NULL);
	return (heap);
}

void		*fit_block_tiny_small(void *heap, size_t size)
{
	void	*block;
	void	*next;
	size_t	aligned_size;

	block = payload(heap);
	next = NULL;
	aligned_size = size_alignment(size, sizeof(void *));
	while (block)
	{
		if (!(meta(block)->flags & INUSE) && fit_in(heap, block, aligned_size))
		{
			next = meta(block)->next ? meta(block)->next :
				block + sizeof(t_meta) + aligned_size;
			set_meta(block, size, INUSE, next);
			break ;
		}
		block = meta(block)->next;
	}
	return (block);
}

void		*fit_block(void **heap, size_t size)
{
	void	*block;

	if (!*heap && !(*heap = init_heap(size)))
		return (NULL);
	if (size <= SMALL)
		block = fit_block_tiny_small(*heap, size);
	else
		block = fit_block_large(*heap, size);
	if (block)
		return (block);
	return (fit_block(&(meta(*heap))->next, size));
}
