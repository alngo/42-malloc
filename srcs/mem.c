/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:13:10 by alngo             #+#    #+#             */
/*   Updated: 2020/02/19 13:50:03 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s1)[i] = ((unsigned char *)s2)[i];
		i++;
	}
	return (s1);
}

void			*ft_memset(void *dst, int c, size_t n)
{
	size_t		i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = (unsigned char)c;
		i++;
	}
	return (dst);
}

void			ft_bzero(void *dst, size_t n)
{
	ft_memset(dst, '\0', n);
}
