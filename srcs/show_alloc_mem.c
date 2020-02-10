/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 13:22:43 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 17:46:10 by alngo            ###   ########.fr       */
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

void			ft_putstr(const char *str, const char *end)
{
	write(1, str, ft_strlen(str));
	write(1, end, ft_strlen(end));
}

void			print_allocation(const char *name, void *heap, size_t *acc)
{
	(void)acc;
	void		*block;
	t_meta		*data;

	ft_putstr(name, " : ");
	if (!heap)
	{
		ft_putstr("(null)", "\n");
		return ;
	}
	data = get_meta(heap);
	block = (data->flags & MMAPD) ? heap : get_payload(heap);
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
	ft_putstr("Total : ", "");
	ft_putstr("\n", "");
}
