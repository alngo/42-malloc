/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:22:43 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 13:44:56 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			print_block(void *payload, t_meta *data)
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

void			print_allocation(const char *name, void *heap, size_t *acc,
		void (*out)(void *, t_meta *))
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
		out(payload(block), meta(block));
		if (meta(block)->flags & INUSE)
			*acc += meta(block)->size;
		block = meta(block)->next;
	}
	if (meta(heap)->next && meta(heap)->flags != (INUSE | MMAPD))
		print_allocation(name, meta(heap)->next, acc, out);
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
		print_allocation(names[index], heaps[index], &acc, &print_block);
		index++;
	}
	ft_putstr("Total : ");
	ft_putnbr(acc, 10);
	ft_putstr(" octets\n");
}
