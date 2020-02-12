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

void		free(void *ptr)
{
	void	*block;
	void 	*heap;
	t_meta	*data;

	heap = NULL;
	if (!ptr || !(block = get_block(ptr, &heap)))
		return ;
	data = get_meta(block);
	set_meta(block, data->size, data->flags ^ INUSE, data->next);
}
