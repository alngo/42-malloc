/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:38:00 by alngo             #+#    #+#             */
/*   Updated: 2020/01/28 10:49:26 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

MU_TEST(malloc_test_invalid_size)
{
	void		*ptr_max;
	void		*ptr_zero;
	void		*ptr_neg;

	ptr_max = malloc(~(size_t)0);
	ptr_zero = malloc(0);
	ptr_neg = malloc(-1);

	mu_check(ptr_max == NULL);
	mu_check(ptr_zero == NULL);
	mu_check(ptr_neg == NULL);
}

MU_TEST_SUITE(malloc_test_suite)
{
	MU_RUN_TEST(malloc_test_invalid_size);
}

int	malloc_test()
{
	MU_RUN_SUITE(malloc_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
