/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:21:08 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 14:33:14 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void 		*tiny_small_realloc(void *ptr, t_meta *data, size_t size)
{
	void	*block;
	void	*new_ptr;

	new_ptr = NULL;
	if (size <= data->size || size < (size_t)(data->next - ptr))
	{
		set_meta(data, size, data->flags | INUSE, data->next);
		return (ptr);
	}
	if (size <= TINY)
		block = get_block(&g_arena.tiny, size);
	else if (size <= SMALL)
		block = get_block(&g_arena.small, size);
	else
		block = get_block(&g_arena.large, size);
	if (block)
	{
		new_ptr = get_payload(block);
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
}


void		*large_realloc(void *ptr, t_meta *data, size_t size)
{
	void	*new_ptr;

	if (size == data->size)
		return (ptr);
	if (!(new_ptr = malloc(size)))
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

void		*minimum_sized_realloc(void *ptr)
{
	free(ptr);
	return (malloc(0));
}

void		*realloc(void *ptr, size_t size)
{
	void 	*block;
	t_meta  *data;

	if (!ptr)
		return (malloc(size));
	if (!(block = get_block_at(ptr, NULL)))
		return (NULL);
	data = get_meta(block);
	if (data->flags & MMAPD)
		return (large_realloc(ptr, data, size));
	else if (size == 0)
		return (minimum_sized_realloc(ptr));
	return (tiny_small_realloc(ptr, data, size));
}
