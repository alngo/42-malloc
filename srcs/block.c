/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:03:38 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 12:05:04 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*get_block_large(void *ptr, void *start, void **heap)
{
	void	*page;

	page = start;
	while (page)
	{
		if (payload(page) == ptr && meta(page)->flags & INUSE)
		{
			if (heap)
				*heap = page;
			return (page);
		}
		page = meta(page)->next;
	}
	return (NULL);
}

void		*get_block_tiny_small(void *ptr, void *start, void **heap)
{
	void	*block;
	void	*page;

	page = start;
	block = payload(page);
	while (page)
	{
		while (block)
		{
			if (payload(block) == ptr && meta(block)->flags & INUSE)
			{
				if (heap)
					*heap = page;
				return (block);
			}
			block = meta(block)->next;
		}
		page = meta(page)->next;
		block = payload(page);
	}
	return (NULL);
}

void		*get_block(void *ptr, void **heap)
{
	void	*target;

	target = NULL;
	if ((target = get_block_tiny_small(ptr, g_arena.tiny, heap)))
		return (target);
	else if ((target = get_block_tiny_small(ptr, g_arena.small, heap)))
		return (target);
	else if ((target = get_block_large(ptr, g_arena.large, heap)))
		return (target);
	return (NULL);
}
