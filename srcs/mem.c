/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 13:13:10 by alngo             #+#    #+#             */
/*   Updated: 2020/02/20 09:21:14 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*ft_memcpy(void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (DCALLTRACE >= 2)
		debug_process("ft_memcpy", 2);
	while (i < n)
	{
		((unsigned char *)s1)[i] = ((unsigned char *)s2)[i];
		i++;
	}
	return (s1);
}
