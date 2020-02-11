/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:51:55 by alngo             #+#    #+#             */
/*   Updated: 2020/02/11 16:12:44 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			ft_putstr(const char *str)
{
	size_t		len;
	const char	*us;

	us = str;
	while (*us)
		us++;
	len = us - str;
	write(1, str, len);
}

void			ft_put2str(const char *str1, const char *str2)
{
	if (str1)
		ft_putstr(str1);
	if (str2)
		ft_putstr(str2);
}

void			ft_nbr_out(size_t value, size_t len, unsigned int base)
{
	size_t		i;
	char		str[len];
	char		*cipher;

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

char			*ft_putnbr(size_t value, unsigned int base)
{
	size_t		i;
	size_t		len;

	i = value;
	len = base == 16 ? 3 : 1;
	while (i /= base)
		len++;
	ft_nbr_out(value, len, base);
	return (NULL);
}
