/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:20:19 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 16:32:00 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void		free(void *ptr)
{
	void	*block;
	void 	*heap;
	t_meta	*data;
	uint8_t is_large;

	heap = NULL;
	if (!ptr || !(block = get_block(ptr, &heap)))
		return ;
	data = get_meta(block);
	is_large = data->flags == (INUSE | MMAPD);
	set_meta(data, data->size, data->flags ^ INUSE, data->next);
	if (is_empty_heap(is_large ? heap : get_payload(heap)))
		delete_heap(heap);
}
