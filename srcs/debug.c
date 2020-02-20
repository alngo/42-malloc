/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:35:29 by alngo             #+#    #+#             */
/*   Updated: 2020/02/20 11:14:11 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				debug_block(void *payload, t_meta *data)
{
	ft_putstr("---------------------------------------------\n");
	ft_putstr("\033[0;32mstart: ");
	ft_putnbr((size_t)(void *)data, 16);
	ft_putstr("\n---------------------------------------------\n");
	ft_putstr("\033[0;34msize:  ");
	ft_putnbr(data->size, 10);
	ft_putstr("\n\033[0;33mflags: ");
	ft_putnbr(data->flags, 2);
	ft_putstr("\n\033[0;36mnext:  ");
	ft_putnbr((size_t)data->next, 16);
	ft_putstr("\033[0m\n");
	if (HEXMEM)
	{
		ft_putmem(payload, HEXMEM == 1 ? data->size : HEXMEM);
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
	names[0] = "\033[0;31mTINY\033[0m";
	names[1] = "\033[0;31mSMALL\033[0m";
	names[2] = "\033[0;31mLARGE\033[0m";
	ft_putstr(">>> DEBUG: ");
	ft_putstr(name);
	ft_putstr(":\n====================================\n");
	while (index < 3)
	{
		print_allocation(names[index], heaps[index], &acc, &debug_block);
		index++;
	}
	ft_putstr("Total : ");
	ft_putnbr(acc, 10);
	ft_putstr(" octets\n");
	ft_putstr(":\n====================================\n");
}

void				debug_call(const char *name, size_t size,
		void *ptr)
{
	ft_putstr("CALL: ");
	ft_putstr(name);
	ft_putstr(" -- ");
	if (size)
	{
		ft_putnbr(size, 10);
		ft_putstr(" octets | ");
	}
	if (ptr)
	{
		ft_putnbr((size_t)ptr, 16);
	}
	ft_putstr("\n");
}

void				debug_process(const char *name, int depth)
{
	while (depth > 0)
	{
		ft_putstr("\t");
		depth--;
	}
	ft_putstr(name);
	ft_putstr("\n");
}
