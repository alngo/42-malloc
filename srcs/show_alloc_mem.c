/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:22:43 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 12:06:06 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			show_block(void *payload, t_meta *data)
{
	if (data->flags & INUSE)
	{
		ft_putnbr((size_t)payload, 16);
		ft_putstr(" - ");
		ft_putnbr((size_t)payload + data->size, 16);
		ft_putstr(" : ");
		ft_putnbr(data->size, 10);
		ft_putstr(" octets\n");
	}
}

void			show_block_info(void *payload, t_meta *data)
{
	(void)payload;
	if (data->size)
	{
		ft_putstr("start: ");
		ft_putnbr((size_t)(void *)data, 16);
		ft_putstr(" | size: ");
		ft_putnbr(data->size, 10);
		ft_putstr(" | flags: ");
		ft_putnbr(data->flags, 2);
		ft_putstr(" | next: ");
		ft_putnbr((size_t)data->next, 16);
		ft_putstr("\n");
	}
}

void			print_block(void *payload, t_meta *data)
{
	if (DEBUG)
		show_block_info(payload, data);
	else
		show_block(payload, data);
}

void			print_allocation(const char *name, void *heap, size_t *acc)
{
	void		*block;

	ft_putstr(name);
	ft_putstr(" : ");
	ft_putnbr((size_t)heap, 16);
	ft_putstr("\n");
	if (!heap)
		return ;
	block = (meta(heap)->flags & INUSE) ? heap : payload(heap);
	while (block)
	{
		print_block(payload(block), meta(block));
		*acc += meta(block)->size;
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
	ft_putstr("Total : ");
	ft_putnbr(acc, 10);
	ft_putstr(" octets\n");
}
