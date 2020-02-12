/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 13:03:38 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 18:06:42 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void 		*get_block_large(void *ptr, void *start, void **heap)
{
	void 	*page;
	void 	*payload;
	t_meta 	*data;

	page = start;
	while (page)
	{
		data = get_meta(page);
		payload = get_payload(page);
		if (payload == ptr && data->flags & INUSE)
			break ;
		page = data->next;
	}
	if (heap)
		*heap = page;
	return (page);
}

void 		*get_block_tiny_small(void *ptr, void *start, void **heap)
{
	void 	*block;
	void 	*payload;
	t_meta 	*page;
	t_meta 	*data;

	page = start;
	while (page)
	{
		page = get_meta(page);
		block = get_payload(page);
		while (block)
		{
			data = get_meta(block);
			payload = get_payload(block);
			if (payload == ptr && data->flags & INUSE)
				break ;
			block = data->next;
		}
		page = page->next;
	}
	if (heap)
		*heap = page;
	return (block);
}

void		*get_block(void *ptr, void **heap)
{
	void	*target;

	target = NULL;
	if ((target = get_block_tiny_small(ptr, &g_arena.tiny, heap)))
		return (target);
	else if ((target = get_block_tiny_small(ptr, &g_arena.small, heap)))
		return (target);
	else if ((target = get_block_large(ptr, &g_arena.large, heap)))
		return (target);
	return (target);
}
