/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:19:11 by alngo             #+#    #+#             */
/*   Updated: 2020/02/13 13:26:27 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incs/malloc.h"
#include <unistd.h>
#include <string.h>

void		print(char *s)
{
	write(1, s, strlen(s));
}

int			main(void)
{
	char	*addr;
	char	*addr3;

	addr = malloc(16);
	free(NULL);
	free((void *)addr + 5);
	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjour\n");
	return (0);
}
