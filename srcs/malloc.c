/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:18:41 by alngo             #+#    #+#             */
/*   Updated: 2020/01/27 17:44:41 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_arena		arenas = {NULL, NULL, NULL};

int			get_type(size_t size)
{
	if (size < TINY)
		return (TINY);
	else if (size < SMALL)
		return (SMALL);
	return (LARGE);
}

void		*get_chunk(void *heap, size_t size)
{
	(void)heap;
	(void)size;
	return (NULL);
}

void *malloc(size_t size)
{
	int		type;
	void	*chunk;

	type = get_type(size);
	if (size <= 0 || size > (~(size_t)0 >> 3))
		return (NULL);
	if (type == TINY)
		chunk = get_chunk(&arenas.tiny, size);
	else if (type == SMALL)
		chunk = get_chunk(&arenas.small, size);
	else if (type == LARGE)
		return (get_chunk(&arenas.large, size));
	return (NULL);
}


size_t	size_alignment(size_t size, size_t alignment)
{
	return ((size + (alignment - 1)) & ~(alignment - 1));
}
