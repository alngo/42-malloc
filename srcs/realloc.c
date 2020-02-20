/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:21:08 by alngo             #+#    #+#             */
/*   Updated: 2020/02/20 11:19:19 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc_minimum_size(void *ptr)
{
	void	*block;

	if (DCALLTRACE >= 1)
		debug_process("realloc_large", 1);
	free(ptr);
	if (!(block = malloc(0)))
		return (NULL);
	return (block - sizeof(t_meta));
}

void		*realloc_large(void *ptr, t_meta *data, size_t size)
{
	void	*block;

	if (DCALLTRACE >= 1)
		debug_process("realloc_large", 1);
	if (size == data->size)
		return (ptr);
	if (!(block = malloc(size)))
		return (NULL);
	ft_memcpy(block, ptr, data->size <= size ? data->size : size);
	free(ptr);
	return (block - sizeof(t_meta));
}

void		*realloc_tiny_small(void *ptr, t_meta *data, size_t size)
{
	void	*block;

	if (DCALLTRACE >= 1)
		debug_process("realloc_tiny_small", 1);
	if (size <= data->size || size < (size_t)(data->next - ptr))
	{
		set_meta(data, size, data->flags | INUSE, data->next);
		return (ptr - sizeof(t_meta));
	}
	if (!(block = malloc(size)))
		return (NULL);
	ft_memcpy(block, ptr, data->size <= size ? data->size : size);
	free(ptr);
	return (block - sizeof(t_meta));
}

void		*realloc(void *ptr, size_t size)
{
	void	*block;
	void	*new_block;

	lock();
	if (DCALLTRACE)
		debug_call("realloc    ", size, ptr);
	if (!ptr)
		return (malloc(size));
	if (!(block = get_block(ptr, NULL)))
		return (NULL);
	if (size == 0)
		new_block = realloc_minimum_size(ptr);
	else if (meta(block)->flags & MMAPD)
		new_block = realloc_large(ptr, meta(block), size);
	else
		new_block = realloc_tiny_small(ptr, meta(block), size);
	if (DCALLTRACE)
		debug_call("realloc_end", size, new_block);
	if (DEBUG)
		debug_output("realloc");
	unlock();
	return (block ? payload(new_block) : NULL);
}
