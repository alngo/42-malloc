/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:51:55 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 15:54:09 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void				ft_putstr(const char *str)
{
	size_t			len;
	const char		*us;

	us = str;
	while (*us)
		us++;
	len = us - str;
	write(1, str, len);
}

void				ft_nbr_out(size_t value, size_t len, unsigned int base)
{
	size_t			i;
	char			str[len];
	char			*cipher;

	i = value;
	cipher = "0123456789ABCDEF";
	str[len] = '\0';
	str[--len] = cipher[i % base];
	while ((i /= base))
		str[--len] = cipher[i % base];
	if (base == 16)
	{
		str[--len] = 'x';
		str[--len] = '0';
	}
	ft_putstr(str);
}

void				ft_putnbr(size_t value, unsigned int base)
{
	size_t			i;
	size_t			len;

	i = value;
	len = base == 16 ? 3 : 1;
	while (i /= base)
		len++;
	ft_nbr_out(value, len, base);
}

static void			print_memory_pad(size_t i, char *buf)
{
	size_t			pad;

	pad = i % 16;
	while (i % 16)
	{
		write(1, "  ", 2);
		i++;
		if (!(i % 2) && i)
			write(1, " ", 1);
	}
	write(1, buf, pad);
	if (pad)
		write(1, "\n", 1);
}

void				ft_putmem(const void *ptr, size_t n)
{
	unsigned char	*tmp;
	char			*hex;
	char			buf[17];
	size_t			i;

	hex = "0123456789abcdef";
	ft_memcpy((void *)buf, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\n", 17);
	tmp = (unsigned char *)ptr;
	i = 0;
	while (i < n)
	{
		write(1, &hex[(*tmp >> 4)], 1);
		write(1, &hex[(*tmp & 0xf)], 1);
		buf[i % 16] = (((*tmp) >= 33 && (*tmp) <= 126) ? *tmp : '.');
		i++;
		if (!(i % 2) && i)
			write(1, " ", 1);
		if (!(i % 16) && i)
			write(1, buf, 17);
		tmp++;
	}
	print_memory_pad(i, buf);
}
