/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:20:19 by alngo             #+#    #+#             */
/*   Updated: 2020/02/25 11:03:52 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		free(void *ptr)
{
	void	*block;
	void	*heap;
	uint8_t	is_large;

	lock();
	if (DCALLTRACE)
		debug_call("free       ", 0, ptr);
	heap = NULL;
	if (!ptr || !(block = get_block(ptr, &heap)))
		return ;
	is_large = meta(block)->flags == (INUSE | MMAPD);
	set_meta(block, meta(block)->size,
			meta(block)->flags ^ INUSE, meta(block)->next);
	if (is_empty_heap(is_large ? heap : payload(heap)))
		delete_heap(heap);
	if (DCALLTRACE)
		debug_call("free_end   ", 0, ptr);
	if (DEBUG)
		debug_output("free");
	unlock();
}
