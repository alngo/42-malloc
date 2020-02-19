/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:18:41 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 16:06:02 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_arena		g_arena = {NULL, NULL, NULL};

void		*malloc(size_t size)
{
	void	*block;

	if (DCALL)
		debug_call("malloc", size, 10);
	if (size > (~(size_t)0 >> 3))
		return (NULL);
	if (size <= TINY)
		block = fit_block(&g_arena.tiny, size);
	else if (size <= SMALL)
		block = fit_block(&g_arena.small, size);
	else
		block = fit_block(&g_arena.large, size);
	if (DEBUG)
		debug_output("malloc");
	if (block)
		return (payload(block));
	return (NULL);
}
