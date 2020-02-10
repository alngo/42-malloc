/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:22:43 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 18:13:39 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <stdio.h>

size_t			ft_strlen(const char *s)
{
	const char	*us;

	us = s;
	while (*us)
		us++;
	return (us - s);
}

void			ft_putstrend(const char *str, const char *end)
{
	write(1, str, ft_strlen(str));
	write(1, end, ft_strlen(end));
}

char			*ft_itoa_base(size_t value, unsigned int base)
{
	char		*cipher;

	cipher = "0123456789ABCDEF";
	(void)value;
	(void)base;
	return ("[]");
}

void			print_allocation(const char *name, void *heap, size_t *acc)
{
	void		*block;
	void		*payload;
	t_meta		*heap_data;
	t_meta		*data;

	ft_putstrend(name, " : ");
	ft_putstrend(ft_itoa_base((size_t)heap, 16), "\n");
	if (!heap)
		return ;
	heap_data = get_meta(heap);
	block = (heap_data->flags & INUSE) ? heap : get_payload(heap);
	while (block)
	{
		data = get_meta(block);
		payload = get_payload(block);
		if (data->flags & INUSE)
		{
			ft_putstrend(ft_itoa_base((size_t)payload, 16), " - ");
			ft_putstrend(ft_itoa_base((size_t)payload + data->size, 16), " : ");
			ft_putstrend(ft_itoa_base(data->size, 10), " octets\n");
			*acc += data->size;
		}
		block = data->next;
	}
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
	ft_putstrend("Total : ", "");
	ft_putstrend(ft_itoa_base(acc, 10), " octets\n");
}
