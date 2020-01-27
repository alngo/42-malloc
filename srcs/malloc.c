/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:18:41 by alngo             #+#    #+#             */
/*   Updated: 2020/01/27 16:14:14 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_arena		arenas = {NULL, NULL, NULL};

void *malloc(size_t size)
{
	if (size <= 0 || size > (~(size_t)0 >> 3))
		return (NULL);
	return (NULL);
}

size_t	size_alignment(size_t size, size_t alignment)
{
	return ((data_size + (alignment - 1)) & ~(alignment - 1));
}
