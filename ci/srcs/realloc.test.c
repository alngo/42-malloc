/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:03:54 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 12:08:14 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"


MU_TEST(realloc_test_basics)
{
	mu_check(1 == 1);
}

MU_TEST_SUITE(realloc_test_suite)
{
	MU_RUN_TEST(realloc_test_basics);
}

int realloc_test()
{
	printf("Run realloc test suite:\n");
	MU_RUN_SUITE(realloc_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
