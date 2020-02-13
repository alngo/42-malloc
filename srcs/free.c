/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:20:19 by alngo             #+#    #+#             */
/*   Updated: 2020/02/13 13:59:59 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void		free(void *ptr)
{
	void	*block;
	void	*heap;
	uint8_t	is_large;

	heap = NULL;
	if (!ptr || !(block = get_block(ptr, &heap)))
		return ;
	is_large = meta(block)->flags == (INUSE | MMAPD);
	set_meta(meta(block), meta(block)->size,
			meta(block)->flags ^ INUSE, meta(block)->next);
	if (is_empty_heap(is_large ? heap : payload(heap)))
	{
		printf("DEBUG: is_empty\n");
		delete_heap(heap);
	}
}
