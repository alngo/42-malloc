/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:47:49 by alngo             #+#    #+#             */
/*   Updated: 2020/02/11 16:23:15 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

MU_TEST(show_alloc_mem_42_test)
{
	void	*addr1;
	void	*addr2;
	void	*addr3;
	void	*addr4;
	void	*addr5;

	addr1 = malloc(1024);
	addr2 = malloc(1024 * 32);
	addr3 = malloc(1024 * 1024);
	addr4 = malloc(1024 * 1024 * 16);
	addr5 = malloc(1024 * 1024 * 128);

	printf("--------------------------------\n");
	show_alloc_mem();
	printf("--------------------------------\n");

	free(addr1);
	free(addr2);
	free(addr3);
	free(addr4);
	free(addr5);
}

MU_TEST(show_alloc_mem_basic_test)
{
	printf("--------------------------------\n");
	show_alloc_mem();
	printf("--------------------------------\n");
}

MU_TEST_SUITE(show_alloc_mem_test_suite)
{
	MU_RUN_TEST(show_alloc_mem_basic_test);
	MU_RUN_TEST(show_alloc_mem_42_test);
}

int show_alloc_mem_test()
{
	printf("Run show_alloc_mem test suite:\n");
	MU_RUN_SUITE(show_alloc_mem_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
