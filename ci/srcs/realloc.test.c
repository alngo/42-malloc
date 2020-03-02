/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:03:54 by alngo             #+#    #+#             */
/*   Updated: 2020/03/02 14:13:53 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static char *rand_string(char *str, size_t size)
{
	const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK1234567890";
	if (size) {
		--size;
		for (size_t n = 0; n < size; n++) {
			int key = rand() % (int) (sizeof charset - 1);
			str[n] = charset[key];
		}
		str[size] = '\0';
	}
	return str;
}

MU_TEST(realloc_test_large_to_tiny)
{
	void	*ptr_a;
	void	*ptr_b;
	t_meta	*meta_a;
	t_meta	*meta_b;

	ptr_a = malloc(5000);
	ptr_b = realloc(ptr_a, 42);

	meta_a = meta(ptr_a - sizeof(t_meta));
	meta_b = meta(ptr_b - sizeof(t_meta));

	free(ptr_a);
	free(ptr_b);
}

MU_TEST(realloc_test_large_and_free)
{
	char	*ptr_a;
	char	*ptr_b;
	char	*ptr_c;
	char	str[5000];

	rand_string(str, 5000);
	ptr_a = (char *)malloc(5000);
	ptr_c = (char *)malloc(5000);
	for (int i = 0; i < 5000; i++)
		ptr_a[i] = str[i];
	ptr_b = (char *)realloc(ptr_a, 42);
	for (int i = 0; i < 42; i++)
		mu_check(ptr_b[i] == str[i]);
	mu_check(ptr_b != ptr_a);
	free(ptr_a);
	free(ptr_c);
	free(ptr_b);
}

MU_TEST(realloc_test_large_payload)
{
	char	*ptr_a;
	char	*ptr_b;
	char	str[5000];

	rand_string(str, 5000);
	ptr_a = (char *)malloc(5000);
	for (int i = 0; i < 5000; i++)
		ptr_a[i] = str[i];
	ptr_b = (char *)realloc(ptr_a, 42);
	for (int i = 0; i < 42; i++)
		mu_check(ptr_b[i] == str[i]);
	mu_check(ptr_b != ptr_a);
	free(ptr_a);
	free(ptr_b);
}

MU_TEST(realloc_test_small_payload)
{
	char	*ptr_a;
	char	*ptr_b;
	char	str[10];

	rand_string(str, 10);
	ptr_a = (char *)malloc(10);
	for (int i = 0; i < 10; i++)
		ptr_a[i] = str[i];
	ptr_b = (char *)realloc(ptr_a, 42);
	for (int i = 0; i < 10; i++)
		mu_check(ptr_b[i] == str[i]);
	mu_check(ptr_b != ptr_a);
	free(ptr_a);
	free(ptr_b);
}

MU_TEST(realloc_test_greater_size)
{
	void	*ptr_a;
	void	*ptr_b;
	t_meta	*meta_a;
	t_meta	*meta_b;

	ptr_a = malloc(5);
	ptr_b = realloc(ptr_a, 42);

	meta_a = meta(ptr_a - sizeof(t_meta));
	meta_b = meta(ptr_b - sizeof(t_meta));

	mu_check(ptr_a != ptr_b);
	mu_check(meta_a->flags == 0x0);
	mu_check(meta_a->size == 5);
	mu_check(meta_a->next == ptr_a + 16);

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

	meta_a = meta(ptr_a - sizeof(t_meta));
	meta_b = meta(ptr_b - sizeof(t_meta));

	mu_check(ptr_a == ptr_b);
	mu_check(meta_b->size == 7);
	mu_check(meta_b->next == ptr_a + 16);

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

	meta_a = meta(ptr_a - sizeof(t_meta));
	meta_b = meta(ptr_b - sizeof(t_meta));

	mu_check(ptr_a == ptr_b);
	mu_check(meta_b->size == 10);
	mu_check(meta_b->next == ptr_a + 48);

	free(ptr_a);
	free(ptr_b);
}

MU_TEST(realloc_test_multiple_call)
{
	void		*ptr[5000];

	for (size_t i = 1; i < 5000; i += 3)
	{
		ptr[i] = realloc(NULL, i);
		if (ptr[i] == NULL)
			mu_fail("Ptr is null");
		if ((uintptr_t)ptr[i] % 16 != 0)
			mu_fail("bad alignment");
		memset(ptr[i], 'a', i);
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

MU_TEST(realloc_test_same_size)
{
	void		*ptr[5000];

	for (size_t i = 1; i < 5000; i += 3)
	{
		ptr[i] = malloc(i);
		if (ptr[i] == NULL)
			mu_fail("Ptr is null");
		ptr[i] = realloc(ptr[i], i);
		if (ptr[i] == NULL)
			mu_fail("Ptr is null");
		if ((uintptr_t)ptr[i] % 16 != 0)
			mu_fail("bad alignment");
		memset(ptr[i], 'a', i);
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

MU_TEST(realloc_test_memset1)
{
	void		*ptr[5000];

	for (size_t i = 1; i < 5000; i += 3)
	{
		ptr[i] = malloc(i);
		if (ptr[i] == NULL)
			mu_fail("Ptr is null");
		if ((uintptr_t)ptr[i] % 16 != 0)
			mu_fail("bad alignment");
		memset(ptr[i], 'a', i);
	}

	for (size_t i = 1; i < 5000; i += 3)
	{
		char	cmp[i];

		ptr[i] = realloc(ptr[i], i);
		if (ptr[i] == NULL)
			mu_fail("Ptr is null");
		if ((uintptr_t)ptr[i] % 16 != 0)
			mu_fail("bad alignment");
		memset(ptr[i], 'a', i);

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

MU_TEST(realloc_test_memset2)
{
	void		*ptr[5000];

	for (size_t i = 2; i < 5000; i += 3)
	{
		ptr[i] = malloc(i);
		if (ptr[i] == NULL)
			mu_fail("Ptr is null");
		if ((uintptr_t)ptr[i] % 16 != 0)
			mu_fail("bad alignment");
		memset(ptr[i], 'a', i);
	}

	for (size_t i = 2; i < 5000; i += 3)
	{
		char	cmp[i / 2];

		ptr[i] = realloc(ptr[i], i / 2);
		if (ptr[i] == NULL)
			mu_fail("Ptr is null");
		if ((uintptr_t)ptr[i] % 16 != 0)
			mu_fail("bad alignment");

		memset(cmp, 'a', i / 2);
		if (memcmp(cmp, ptr[i], i / 2) != 0)
			mu_fail("Segment is corrupted: ");
	}

	for (size_t i = 2; i < 5000; i += 3)
	{
		char	cmp[i / 2];

		memset(cmp, 'a', i / 2);
		if (memcmp(cmp, ptr[i], i / 2) != 0)
			mu_fail("Segment is corrupted: ");
	}

	for (size_t i = 2; i < 5000; i += 3)
	{
		char	cmp[i / 2];

		memset(cmp, 'a', i / 2);
		if (memcmp(cmp, ptr[i], i / 2) != 0)
			mu_fail("Segment is corrupted: ");
		free(ptr[i]);
	}
}

MU_TEST(realloc_test_memset3)
{
	void		*ptr[5000];

	for (size_t i = 1; i < 5000; i += 3)
	{
		ptr[i] = malloc(i);
		if (ptr[i] == NULL)
			mu_fail("Ptr is null");
		if ((uintptr_t)ptr[i] % 16 != 0)
			mu_fail("bad alignment");
		memset(ptr[i], 'a', i);
	}

	for (size_t i = 1; i < 5000; i += 3)
	{
		char	cmp[i];

		ptr[i] = realloc(ptr[i], i * 2);
		if (ptr[i] == NULL)
			mu_fail("Ptr is null");
		if ((uintptr_t)ptr[i] % 16 != 0)
			mu_fail("bad alignment");

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

MU_TEST(realloc_test_memset4)
{
	void		*ptr[5000];

	for (size_t i = 1; i < 5000; i += 3)
	{
		ptr[i] = malloc(i);
		if (ptr[i] == NULL)
			mu_fail("Ptr is null");
		if ((uintptr_t)ptr[i] % 16 != 0)
			mu_fail("bad alignment");
		memset(ptr[i], 'a', i);
	}

	for (size_t i = 1; i < 5000; i += 3)
	{
		char	cmp[i];

		ptr[i] = realloc(ptr[i], i * 2);
		if (ptr[i] == NULL)
			mu_fail("Ptr is null");
		if ((uintptr_t)ptr[i] % 16 != 0)
			mu_fail("bad alignment");
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


MU_TEST_SUITE(realloc_test_suite)
{
	MU_RUN_TEST(realloc_test_lower_size);
	MU_RUN_TEST(realloc_test_slightly_greater_size);
	MU_RUN_TEST(realloc_test_greater_size);
	MU_RUN_TEST(realloc_test_small_payload);
	MU_RUN_TEST(realloc_test_large_payload);
	MU_RUN_TEST(realloc_test_large_to_tiny);
	MU_RUN_TEST(realloc_test_multiple_call);
	MU_RUN_TEST(realloc_test_same_size);
	MU_RUN_TEST(realloc_test_memset1);
	MU_RUN_TEST(realloc_test_memset2);
	MU_RUN_TEST(realloc_test_memset3);
	MU_RUN_TEST(realloc_test_memset4);
}

int realloc_test()
{
	printf("Run realloc test suite:\n");
	MU_RUN_SUITE(realloc_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
