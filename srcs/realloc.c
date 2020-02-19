/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:21:08 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 16:08:15 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*realloc_minimum_size(void *ptr)
{
	void	*block;

	free(ptr);
	if (!(block = malloc(0)))
		return (NULL);
	return (block - sizeof(t_meta));
}

void		*realloc_large(void *ptr, t_meta *data, size_t size)
{
	void	*block;

	if (size == data->size)
		return (ptr);
	if (!(block = malloc(size)))
		return (NULL);
	debug_block(block, meta(block - sizeof(t_meta)));
	ft_memcpy(block, ptr, size);
	write(1, "DEBUG", 6);
	free(ptr);
	return (block - sizeof(t_meta));
}

void		*realloc_tiny_small(void *ptr, t_meta *data, size_t size)
{
	void	*block;

	if (size <= data->size || size < (size_t)(data->next - ptr))
	{
		set_meta(data, size, data->flags | INUSE, data->next);
		return (ptr - sizeof(t_meta));
	}
	if (!(block = malloc(size)))
		return (NULL);
	ft_memcpy(block, ptr, size);
	free(ptr);
	return (block - sizeof(t_meta));
}

void		*realloc(void *ptr, size_t size)
{
	void	*block;
	void	*new_block;

	if (DCALL)
		debug_call("realloc", (size_t)ptr, 16);
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
	if (DEBUG)
		debug_output("realloc");
	if (block)
		return (payload(new_block));
	else
		return (NULL);
}
