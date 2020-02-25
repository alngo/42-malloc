/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:28:59 by alngo             #+#    #+#             */
/*   Updated: 2020/02/25 10:43:04 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			fit_in(void *heap, void *block, size_t size)
{
	void	*ptr;
	void	*limit;

	ptr = block + sizeof(t_meta) + size;
	limit = heap + meta(heap)->size;
	if (DCALLTRACE >= 4)
		debug_process("fit_in", 4);
	if (meta(block)->flags & INUSE)
		return (0);
	else if (meta(block)->size == 0 && ptr < limit)
		return (1);
	else if (meta(block)->next >= ptr)
		return (1);
	return (0);
}

void		*fit_block_large(void *heap, size_t size)
{
	if (DCALLTRACE >= 3)
		debug_process("fit_block_large", 3);
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
	aligned_size = size_alignment(size, 16);
	if (DCALLTRACE >= 3)
		debug_process("fit_block_tiny_small", 3);
	while (block)
	{
		if (fit_in(heap, block, aligned_size))
		{
			next = meta(block)->next ? meta(block)->next :
				(block + sizeof(t_meta) + aligned_size);
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

	if (DCALLTRACE >= 2)
		debug_process("fit_block", 2);
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
