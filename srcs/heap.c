/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 12:33:28 by alngo             #+#    #+#             */
/*   Updated: 2020/01/28 14:56:20 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

size_t		get_heap_size(size_t size)
{
	int		pagesize;
	int		offset;

	pagesize = getpagesize();
	offset = sizeof(t_meta);
	if (size < TINY)
		return (size_alignment(offset + ((TINY + offset) * 100), pagesize));
	else if (size < SMALL)
		return (size_alignment(offset + ((SMALL + offset) * 100), pagesize));
	return (offset + size);
}

void		*init_heap(size_t size)
{
	size_t	heap_size;
	void	*ptr;

	ptr = NULL;
	heap_size = get_heap_size(size);
	if ((ptr = mmap(ptr, heap_size, PROT_READ | PROT_WRITE,
					MAP_ANON | MAP_SHARED, -1, 0)) == MAP_FAILED)
		return (NULL);
	set_meta(ptr, heap_size, MMAPD, NULL);
	return (ptr);
}
