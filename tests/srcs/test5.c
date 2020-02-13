/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:19:41 by alngo             #+#    #+#             */
/*   Updated: 2020/02/13 13:27:36 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include <unistd.h>
#include <string.h>

int			main(void)
{
	char	*adr1;
	char	*adr2;
	char	*adr3;
	char	*adr4;
	char	*adr5;

	adr1 = malloc(1024);
	adr2 = malloc(1024 * 32);
	adr3 = malloc(1024 * 1024);
	adr4 = malloc(1024 * 1024 * 16);
	adr5 = malloc(1024 * 1024 * 128);
	show_alloc_mem();
	return (0);
}
