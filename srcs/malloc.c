/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:18:41 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 10:51:49 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_arena		g_arena = {NULL, NULL, NULL};

void		debug_malloc(void *block)
{
	ft_putstr("malloc:    ");
	show_block_info(payload(block), meta(block));
}

void		*malloc(size_t size)
{
	void	*block;

	if (size > (~(size_t)0 >> 3))
		return (NULL);
	if (size <= TINY)
		block = fit_block(&g_arena.tiny, size);
	else if (size <= SMALL)
		block = fit_block(&g_arena.small, size);
	else
		block = fit_block(&g_arena.large, size);
	if (block)
	{
		if (DEBUG)
			debug_malloc(block);
		return (payload(block));
	}
	return (NULL);
}
