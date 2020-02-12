/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:22:43 by alngo             #+#    #+#             */
/*   Updated: 2020/02/11 16:48:46 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

void			print_block(void *payload, t_meta *data)
{
	ft_putnbr((size_t)payload, 16);
	ft_putstr(" - ");
	ft_putnbr((size_t)payload + data->size, 16);
	ft_putstr(" : ");
	ft_putnbr(data->size, 10);
	ft_putstr(" octets\n");
}

void			print_allocation(const char *name, void *heap, size_t *acc)
{
	void		*block;

	ft_put2str(name, " : ");
	ft_putnbr((size_t)heap, 16);
	ft_putstr("\n");
	if (!heap)
		return ;
	block = (meta(heap)->flags & INUSE) ? heap : payload(heap);
	while (block)
	{
		if (meta(block)->flags & INUSE)
		{
			print_block(payload(block), meta(block));
			*acc += meta(block)->size;
		}
		block = meta(block)->next;
	}
	if (meta(heap)->next && meta(heap)->flags != (INUSE | MMAPD))
		print_allocation(name, meta(heap)->next, acc);
}

void			show_alloc_mem(void)
{
	uint8_t		index;
	size_t		acc;
	void		*heaps[3];
	char		*names[3];

	acc = 0;
	index = 0;
	heaps[0] = g_arena.tiny;
	heaps[1] = g_arena.small;
	heaps[2] = g_arena.large;
	names[0] = "TINY";
	names[1] = "SMALL";
	names[2] = "LARGE";
	while (index < 3)
	{
		print_allocation(names[index], heaps[index], &acc);
		index++;
	}
	ft_put2str("Total : ", "");
	ft_putnbr(acc, 10);
	ft_putstr(" octets\n");
}
