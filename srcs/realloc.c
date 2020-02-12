/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:21:08 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 16:32:30 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc_tiny_small(void *ptr, t_meta *data, size_t size)
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
		block = fit_block(&g_arena.tiny, size);
	else if (size <= SMALL)
		block = fit_block(&g_arena.small, size);
	else
		block = fit_block(&g_arena.large, size);
	if (block)
	{
		new_ptr = get_payload(block);
		ft_memcpy(new_ptr, ptr, size);
		free(ptr);
	}
	return (new_ptr);
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
	return (new_ptr);
}

void		*realloc_minimum_size(void *ptr)
{
	free(ptr);
	return (malloc(0));
}

void		*realloc(void *ptr, size_t size)
{
	void	*block;
	t_meta	*data;

	if (!ptr)
		return (malloc(size));
	if (!(block = get_block(ptr, NULL)))
		return (NULL);
	data = get_meta(block);
	if (data->flags & MMAPD)
		return (realloc_large(ptr, data, size));
	else if (size == 0)
		return (realloc_minimum_size(ptr));
	return (realloc_tiny_small(ptr, data, size));
}
