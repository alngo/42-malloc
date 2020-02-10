/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:03:54 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 14:33:00 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

MU_TEST(realloc_test_small_payload)
{
	mu_check(1 == 1);
}

MU_TEST(realloc_test_greater_size)
{
	void	*ptr_a;
	void	*ptr_b;

	t_meta	*meta_a;
	t_meta	*meta_b;

	ptr_a = malloc(5);
	ptr_b = realloc(ptr_a, 42);

	meta_a = get_meta(ptr_a - sizeof(t_meta));
	meta_b = get_meta(ptr_b - sizeof(t_meta));

	mu_check(ptr_a != ptr_b);
	mu_check(meta_a->flags == 0x0);
	mu_check(meta_a->size == 5);
	mu_check(meta_a->next == ptr_a + 8);

	mu_check(meta_b->flags == INUSE);
	mu_check(meta_b->size == 42);
	mu_check(meta_b->next == ptr_b + 48);

	free(ptr_a);
	free(ptr_b);
}

MU_TEST(realloc_test_slightly_greater_size)
{
	void	*ptr_a;
	void	*ptr_b;

	t_meta	*meta_a;
	t_meta	*meta_b;

	ptr_a = malloc(5);
	ptr_b = realloc(ptr_a, 7);

	meta_a = get_meta(ptr_a - sizeof(t_meta));
	meta_b = get_meta(ptr_b - sizeof(t_meta));

	mu_check(ptr_a == ptr_b);
	mu_check(meta_b->size == 7);
	mu_check(meta_b->next == ptr_a + 8);

	free(ptr_a);
	free(ptr_b);
}


MU_TEST(realloc_test_lower_size)
{
	void	*ptr_a;
	void	*ptr_b;

	t_meta	*meta_a;
	t_meta	*meta_b;

	ptr_a = malloc(42);
	ptr_b = realloc(ptr_a, 10);

	meta_a = get_meta(ptr_a - sizeof(t_meta));
	meta_b = get_meta(ptr_b - sizeof(t_meta));

	mu_check(ptr_a == ptr_b);
	mu_check(meta_b->size == 10);
	mu_check(meta_b->next == ptr_a + 48);

	free(ptr_a);
	free(ptr_b);
}

MU_TEST_SUITE(realloc_test_suite)
{
	MU_RUN_TEST(realloc_test_lower_size);
	MU_RUN_TEST(realloc_test_slightly_greater_size);
	MU_RUN_TEST(realloc_test_greater_size);
	MU_RUN_TEST(realloc_test_small_payload);
}

int realloc_test()
{
	printf("Run realloc test suite:\n");
	MU_RUN_SUITE(realloc_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
