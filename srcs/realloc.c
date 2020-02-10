/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:21:08 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 12:48:07 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
	void 	*block;
	void	*new_ptr;
	t_meta  *data;
	t_meta	*prec;
	(void)size;

	prec = NULL;
	if (!ptr)
		return (malloc(size));
	if (!(block = get_block_at(ptr, &prec)))
		return (NULL);
	data = get_meta(block);
	if ((data->flags & MMAPD && size > data->size) || size <= 0)
	{
		new_ptr = malloc(size);
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}
