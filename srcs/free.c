/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:20:19 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 10:52:14 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		debug_free(void *block)
{
	ft_putstr("free:      ");
	show_block_info(payload(block), meta(block));
}

void		free(void *ptr)
{
	void	*block;
	void	*heap;
	uint8_t	is_large;

	heap = NULL;
	if (!ptr || !(block = get_block(ptr, &heap)))
		return ;
	is_large = meta(block)->flags == (INUSE | MMAPD);
	if (DEBUG)
		debug_free(block);
	set_meta(meta(block), meta(block)->size,
			meta(block)->flags ^ INUSE, meta(block)->next);
	if (is_empty_heap(is_large ? heap : payload(heap)))
	{
		delete_heap(heap);
	}
}
