/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:38:00 by alngo             #+#    #+#             */
/*   Updated: 2020/03/02 13:53:27 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

MU_TEST(malloc_test_invalid_size)
{
	void		*ptr_max;
	void		*ptr_neg;

	ptr_max = malloc(~(size_t)0);
	ptr_neg = malloc(-1);

	mu_check(ptr_max == NULL);
	mu_check(ptr_neg == NULL);
}

MU_TEST(malloc_test_tiny)
{
	void		*ptr_a;
	void		*ptr_b;
	void		*ptr_zero;
	t_meta		*meta_zero;
	t_meta		*meta_a;
	t_meta		*meta_b;

	ptr_a = malloc(42);
	ptr_b = malloc(10);
	ptr_zero = malloc(0);

	meta_a = meta(ptr_a - sizeof(t_meta));
	meta_b = meta(ptr_b - sizeof(t_meta));
	meta_zero = meta(ptr_zero - sizeof(t_meta));

	mu_check(meta_a->size == 42);
	mu_check(meta_a->flags == INUSE);
	mu_check(meta_a->next == ptr_b - sizeof(t_meta));

	mu_check(meta_b->size == 10);
	mu_check(meta_b->flags == INUSE);
	mu_check(meta_b->next == ptr_b + 16);

	mu_check(meta_zero->size == 0);
	mu_check(meta_zero->flags == INUSE);
	mu_check(meta_zero->next == ptr_zero);

	free(ptr_a);
	free(ptr_b);
	free(ptr_zero);
}

MU_TEST(malloc_test_large)
{
	void		*ptr_a;
	void		*ptr_b;
	t_meta		*meta_a;
	t_meta		*meta_b;

	ptr_a = malloc(5000);
	ptr_b = malloc(5000);

	meta_a = meta(ptr_a - sizeof(t_meta));
	meta_b = meta(ptr_b - sizeof(t_meta));

	mu_check(meta_a->size == 5000);
	mu_check(meta_a->flags == (INUSE | MMAPD));
	mu_check(meta_a->next == ptr_b - sizeof(t_meta));

	mu_check(meta_b->size == 5000);
	mu_check(meta_b->flags == (INUSE | MMAPD));
	mu_check(meta_b->next == NULL);

	free(ptr_a);
	free(ptr_b);
}

MU_TEST(malloc_test_xlarge)
{
	void		*ptr_a;
	t_meta		*meta_a;

	ptr_a = malloc(INT_MAX);
	meta_a = meta(ptr_a - sizeof(t_meta));

	mu_check(meta_a->size == INT_MAX);
	mu_check(meta_a->flags == (INUSE | MMAPD));
	mu_check(meta_a->next == NULL);

	free(ptr_a);
}

MU_TEST(malloc_test_size_alignment)
{
	void		*ptr;

	ptr = malloc(0);
	mu_check((uintptr_t)ptr % 16 == 0);
	free(ptr);
}

MU_TEST(malloc_test_multiple)
{
	void		*ptr;

	for (size_t i = 1; i < 5000; i += 3)
	{
		ptr = malloc(i);
		mu_check(ptr != NULL);
		mu_check((uintptr_t)ptr % 16 == 0);
		memset(ptr, 'a', i);
		free(ptr);
	}
}

MU_TEST(malloc_test_corruption)
{
	void		*ptr[5000];

	for (size_t i = 1; i < 5000; i += 3)
	{
		ptr[i] = malloc(i);
		mu_check(ptr[i] != NULL);
		mu_check((uintptr_t)ptr[i] % 16 == 0);
		memset(ptr[i], 'a', i);
	}

	for (size_t i = 1; i < 5000; i += 3)
	{
		char	cmp[i];
		char	tmp[i + 1];

		memset(cmp, 'a', i);
		if (memcmp(cmp, ptr[i], i) != 0)
		{
			memcpy(tmp, ptr[i], i);
			tmp[i] = 0;
			mu_fail("Segment is corrupted: ");
			write(1, tmp, i);
			write(1, "\n", 1);
		}
		free(ptr[i]);
	}
}

MU_TEST(malloc_test_memset1)
{
	void		*ptr[5000];

	for (size_t i = 1; i < 5000; i += 3)
	{
		ptr[i] = malloc(i);
		mu_check(ptr[i] != NULL);
		mu_check((uintptr_t)ptr[i] % 16 == 0);
	}

	for (size_t i = 1; i < 5000; i += 3)
	{
		memset(ptr[i], 'a', i);
		free(ptr[i]);
	}
}

MU_TEST(malloc_test_memset2)
{
	void		*ptr[5000];

	for (size_t i = 1; i < 5000; i += 3)
	{
		ptr[i] = malloc(i);
		mu_check(ptr[i] != NULL);
		mu_check((uintptr_t)ptr[i] % 16 == 0);
	}

	for (size_t i = 1; i < 5000; i += 3)
	{
		memset(ptr[i], 'a', i);
	}

	for (size_t i = 1; i < 5000; i += 3)
	{
		char	cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, ptr[i], i) != 0)
			mu_fail("Segment is corrupted: ");
		free(ptr[i]);
	}
}

MU_TEST(malloc_test_memset3)
{
	void		*ptr[5000];

	for (size_t i = 1; i < 5000; i += 3)
	{
		ptr[i] = malloc(i);
		mu_check(ptr[i] != NULL);
		memset(ptr[i], 'a', i);
		mu_check((uintptr_t)ptr[i] % 16 == 0);
	}

	for (size_t i = 1; i < 5000; i += 3)
	{
		char	cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, ptr[i], i) != 0)
			mu_fail("Segment is corrupted: ");
	}

	for (size_t i = 1; i < 5000; i += 3)
	{
		char	cmp[i];

		memset(cmp, 'a', i);
		if (memcmp(cmp, ptr[i], i) != 0)
			mu_fail("Segment is corrupted: ");
		free(ptr[i]);
	}
}

MU_TEST(malloc_test_memset4)
{
	void		*ptr[5000];

	for (size_t len = 0; len < 5000; len += 3)
	{
		char	cmp[len];

		memset(cmp, 'a', len);
		for (size_t i = 1; i < 5000; i += 3)
		{
			ptr[i] = malloc(len);
			mu_check(ptr[i] != NULL);
			memset(ptr[i], 'a', len);
			mu_check((uintptr_t)ptr[i] % 16 == 0);
		}

		for (size_t i = 1; i < 5000; i += 3)
		{
			if (memcmp(cmp, ptr[i], len) != 0)
				mu_fail("Segment is corrupted: ");
		}

		for (size_t i = 1; i < 5000; i += 3)
		{
			if (memcmp(cmp, ptr[i], len) != 0)
				mu_fail("Segment is corrupted: ");
			free(ptr[i]);
		}
	}
}

MU_TEST_SUITE(malloc_test_suite)
{
	MU_RUN_TEST(malloc_test_size_alignment);
	MU_RUN_TEST(malloc_test_invalid_size);
	MU_RUN_TEST(malloc_test_tiny);
	MU_RUN_TEST(malloc_test_large);
	MU_RUN_TEST(malloc_test_xlarge);
	MU_RUN_TEST(malloc_test_multiple);
	MU_RUN_TEST(malloc_test_corruption);
	MU_RUN_TEST(malloc_test_memset1);
	MU_RUN_TEST(malloc_test_memset2);
	MU_RUN_TEST(malloc_test_memset3);
	MU_RUN_TEST(malloc_test_memset4);
}

int	malloc_test()
{
	printf("Run malloc test suite:\n");
	MU_RUN_SUITE(malloc_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
