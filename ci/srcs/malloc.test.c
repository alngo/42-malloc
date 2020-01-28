/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:38:00 by alngo             #+#    #+#             */
/*   Updated: 2020/01/28 15:10:24 by alngo            ###   ########.fr       */
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

MU_TEST(malloc_test_tiny)
{
	void		*ptr_a;
	void		*ptr_b;
	t_meta		*meta_a;
	t_meta		*meta_b;
	size_t		alignment;

	ptr_a = malloc(42);
	ptr_b = malloc(10);

	meta_a = get_meta(ptr_a - sizeof(t_meta));
	meta_b = get_meta(ptr_b - sizeof(t_meta));
	mu_check(meta_a->size == 42);
	mu_check(meta_a->flags == INUSE);
	mu_check(meta_a->next == ptr_b - sizeof(t_meta));

	mu_check(meta_b->size == 10);
	mu_check(meta_b->flags == INUSE);
	mu_check(meta_b->next == ptr_b + 16);
}

MU_TEST(malloc_test_large)
{
	void		*ptr_a;
	void		*ptr_b;
	t_meta		*meta_a;
	t_meta		*meta_b;
	size_t		alignment;

	ptr_a = malloc(5000);
	ptr_b = malloc(5000);

	meta_a = get_meta(ptr_a - sizeof(t_meta));
	meta_b = get_meta(ptr_b - sizeof(t_meta));

	mu_check(meta_a->size == 5000);
	mu_check(meta_a->flags == (INUSE | MMAPD));
	mu_check(meta_a->next == ptr_b - sizeof(t_meta));

	mu_check(meta_b->size == 5000);
	mu_check(meta_b->flags == (INUSE | MMAPD));
	mu_check(meta_b->next == NULL);
}

MU_TEST_SUITE(malloc_test_suite)
{
	MU_RUN_TEST(malloc_test_invalid_size);
	MU_RUN_TEST(malloc_test_tiny);
	MU_RUN_TEST(malloc_test_large);
}

int	malloc_test()
{
	printf("Run malloc test suite:\n");
	MU_RUN_SUITE(malloc_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
