/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:28:59 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 11:05:34 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

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
	while (block)
	{
		if (!(meta(block)->flags & INUSE))
		{
			if (meta(block)->size == 0 || meta(block)->size >= size)
			{
				aligned_size = size_alignment(size, sizeof(void *));
				next = block + sizeof(t_meta) + aligned_size;
				if (next > (heap + sizeof(t_meta) + meta(heap)->size))
					next = NULL;
				set_meta(block, size, INUSE, next);
				break ;
			}
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
	if (size > SMALL)
		block = fit_block_large(*heap, size);
	else
		block = fit_block_tiny_small(*heap, size);
	if (block)
		return (block);
	return (fit_block(&(meta(*heap))->next, size));
}
