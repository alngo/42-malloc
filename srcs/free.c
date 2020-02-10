/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:20:19 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 11:58:53 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void		free(void *ptr)
{
	void	*block;
	t_meta	*data;
	t_meta 	*prec;

	prec = NULL;
	if (!ptr || !(block = get_block_at(ptr, &prec)))
		return ;
	data = get_meta(block);
	set_meta(block, data->size, data->flags ^ INUSE, data->next);
	if (data->flags & MMAPD)
	{
		if (prec)
			prec->next = data->next;
		munmap(block, data->size);
	}
}
