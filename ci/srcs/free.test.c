/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:55:07 by alngo             #+#    #+#             */
/*   Updated: 2020/01/28 17:15:31 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#define SIZE 64

MU_TEST(free_test_invalid_pointer)
{
	void	*ptr_null;
	void	*ptr_shifted;

	ptr_shifted = malloc(42) + 21;

	free(ptr_null);
	free(ptr_shifted);
	free(NULL);
}

MU_TEST(free_test_valid_pointer)
{
	void	*ptr_a;
	void	*ptr_b;
	void	*ptr_c;

	t_meta	*meta_a;
	t_meta	*meta_b;
	t_meta	*meta_c;

	ptr_a = malloc(42);
	ptr_b = malloc(1000);
	ptr_c = malloc(5000);

	meta_a = get_meta(ptr_a - sizeof(t_meta));
	meta_b = get_meta(ptr_b - sizeof(t_meta));
	meta_c = get_meta(ptr_c - sizeof(t_meta));

	free(ptr_a);
	free(ptr_b);
	free(ptr_c);

	mu_check(meta_a->flags == 0x0);
	mu_check(meta_b->flags == 0x0);
	mu_check(msync(meta_c, 5000, 0) < 0);
}

MU_TEST_SUITE(free_test_suite)
{
	MU_RUN_TEST(free_test_invalid_pointer);
	MU_RUN_TEST(free_test_valid_pointer);
}

int free_test()
{
	printf("Run free test suite:\n");
	MU_RUN_SUITE(free_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
