/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:18:41 by alngo             #+#    #+#             */
/*   Updated: 2020/02/13 13:27:08 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/malloc.h"
#include <unistd.h>
#include <string.h>

#define M (1024 * 1024)

void		print(char *s)
{
	write(1, s, strlen(s));
}

int			main(void)
{
	char	*addr1;
	char	*addr2;
	char	*addr3;

	addr1 = (char *)malloc(16 * M);
	strcpy(addr1, "Bonjour\n");
	addr2 = (char *)malloc(16 * M);
	print(addr1);
	addr3 = (char *)realloc(addr1, 128 * M);
	addr3[127 * M] = 42;
	print(addr3);
	return (0);
}
