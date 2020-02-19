/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:21:08 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 11:22:32 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void		debug_realloc(void *block, const char *name)
{
	ft_putstr(name);
	show_block_info(payload(block), meta(block));
}

void		*realloc_large(void *ptr, t_meta *data, size_t size)
{
	void	*new_ptr;

	if (size == data->size)
		return (ptr);
	if (!(new_ptr = malloc(size)))
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr - sizeof(t_meta));
}

void		*realloc_tiny_small(void *ptr, t_meta *data, size_t size)
{
	void	*block;

	if (size <= data->size || size < (size_t)(data->next - ptr))
	{
		set_meta(data, size, data->flags | INUSE, data->next);
		return (ptr - sizeof(t_meta));
	}
	if (size <= TINY)
		block = fit_block(&g_arena.tiny, size);
	else if (size <= SMALL)
		block = fit_block(&g_arena.small, size);
	else
		block = fit_block(&g_arena.large, size);
	if (block)
	{
		ft_memcpy(payload(block), ptr, size);
		free(ptr);
	}
	return (block);
}

void		*realloc_minimum_size(void *ptr)
{
	free(ptr);
	return (malloc(0));
}

void		*realloc(void *ptr, size_t size)
{
	void	*block;
	void	*new_block;

	if (!ptr)
		return (malloc(size));
	if (!(block = get_block(ptr, NULL)))
		return (NULL);
	if (DEBUG)
		debug_realloc(block, "old block: ");
	if (meta(block)->flags & MMAPD)
		new_block = realloc_large(ptr, meta(block), size);
	else if (size == 0)
		new_block = realloc_minimum_size(ptr);
	else
		new_block = realloc_tiny_small(ptr, meta(block), size);
	if (DEBUG)
		debug_realloc(new_block, "new block: ");
	return (payload(new_block));
}
