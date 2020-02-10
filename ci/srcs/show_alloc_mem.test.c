/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.test.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:47:49 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 16:50:33 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

MU_TEST(show_alloc_mem_basic_test)
{
	show_alloc_mem();
}

MU_TEST_SUITE(show_alloc_mem_test_suite)
{
	MU_RUN_TEST(show_alloc_mem_basic_test);
}

int show_alloc_mem_test()
{
	printf("Run show_alloc_mem test suite:\n");
	MU_RUN_SUITE(show_alloc_mem_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
