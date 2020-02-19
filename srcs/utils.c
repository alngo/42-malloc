/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 09:23:18 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 13:13:08 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_meta		*meta(void *ptr)
{
	return ((t_meta *)ptr);
}

void		*payload(void *ptr)
{
	return (ptr + sizeof(t_meta));
}

t_meta		*set_meta(void *ptr, size_t size, uint8_t flags, void *next)
{
	t_meta	*meta;

	meta = (t_meta *)ptr;
	meta->size = size;
	meta->flags = flags;
	meta->next = next;
	return (meta);
}

size_t		size_alignment(size_t size, size_t alignment)
{
	return ((size + (alignment - 1)) & ~(alignment - 1));
}
