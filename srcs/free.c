/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:20:19 by alngo             #+#    #+#             */
/*   Updated: 2020/01/28 17:13:43 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void 		*match_block(void *ptr, void *heap)
{
	void	*block;
	void	*block_payload;
	t_meta	*heap_meta;
	t_meta	*block_meta;

	if (!heap)
		return (NULL);
	heap_meta = get_meta(heap);
	block = (heap_meta->flags & INUSE) ? heap : get_payload(heap);
	while (block)
	{
		block_meta = get_meta(block);
		block_payload = get_payload(block);
		if (block_payload == ptr && block_meta->flags & INUSE)
			break;
		block = block_meta->next;
	}
	return (block);
}

void		*get_block_at(void *ptr)
{
	uint8_t	index;
	void	*heaps[3];
	void	*target;

	heaps[0] = g_arena.tiny;
	heaps[1] = g_arena.small;
	heaps[2] = g_arena.large;
	index = 0;
	while (index < 3)
	{
		if ((target = match_block(ptr, heaps[index])))
			break;
		index++;
	}
	return (target);
}

void		free(void *ptr)
{
	void	*block;
	t_meta	*data;

	if (!ptr || !(block = get_block_at(ptr)))
		return ;
	data = get_meta(block);
	set_meta(block, data->size, data->flags ^ INUSE, data->next);
	if (data->flags & MMAPD)
		munmap(block, data->size);
}
