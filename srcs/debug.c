/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:35:29 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 13:54:13 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				block_info(void *payload, t_meta *data)
{
	(void)payload;
	if (data->size)
	{
		ft_putstr("[start: ");
		ft_putnbr((size_t)(void *)data, 16);
		ft_putstr("][next: ");
		ft_putnbr((size_t)data->next, 16);
		ft_putstr("][size: ");
		ft_putnbr(data->size, 10);
		ft_putstr("][flags: ");
		ft_putnbr(data->flags, 2);
		ft_putstr("]\n");
		if (HEXMEM)
		{
			ft_putstr("payload:\n");
			ft_putmem(payload, HEXMEM);
			ft_putstr("\n");
		}
	}
}

void				debug_output(const char *name)
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
	ft_putstr("DEBUG: ");
	ft_putstr(name);
	ft_putstr(":\n====================================\n");
	while (index < 3)
	{
		print_allocation(names[index], heaps[index], &acc, &block_info);
		index++;
	}
	ft_putstr("Total : ");
	ft_putnbr(acc, 10);
	ft_putstr(" octets\n");
	ft_putstr(":\n====================================\n");
}
