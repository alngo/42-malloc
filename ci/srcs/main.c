/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:50:22 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 16:47:11 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int test()
{
	char *ptr;
	char *ptr2;

	ptr = NULL;
	ptr2 = NULL;
	malloc(1536);
	realloc(NULL, 64);
	malloc(32);
	free(0x7FFCE4C00090);
	free(0x7FFCE4C00080);
	free(0x7FFCE4C000B0);
	malloc(32);
	ptr = realloc(NULL, 256);
	ptr2 = realloc(ptr, 768);
	free(ptr2);
	malloc(13);
	malloc(45);
	malloc(269);
	malloc(45);
	malloc(50);
}

int	main(int argc, char *argv[])
{
	utils_test();
	malloc_test();
	free_test();
	realloc_test();
	show_alloc_mem_test();
	test();
	return (MU_EXIT_CODE);
}
