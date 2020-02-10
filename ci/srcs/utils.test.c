/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:39:42 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 16:36:26 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

#define SIZE 64

void		*xalloc()
{
	return (mmap(NULL, SIZE,
				PROT_READ | PROT_WRITE,
				MAP_ANON | MAP_SHARED, -1, 0));
}

void		xfree(void *ptr)
{
	munmap(ptr, SIZE);
}

MU_TEST(utils_test_size_alignment)
{
	int			a;
	int			b;
	int			c;

	a = size_alignment(9, 16);
	b = size_alignment(17, 16);
	c = size_alignment(5678, 4096);

	mu_check(a == 16);
	mu_check(b == 32);
	mu_check(c == 8192);
}

MU_TEST(utils_test_set_meta)
{
	t_meta		*meta_a;
	t_meta		*meta_b;
	t_meta		*meta_c;
	void		*ptr_a;
	void		*ptr_b;
	void		*ptr_c;

	ptr_a = xalloc();
	ptr_b = xalloc();
	ptr_c = xalloc();

	meta_a = set_meta(ptr_a, 42, INUSE | MMAPD, NULL);
	meta_b = set_meta(ptr_b, ~(size_t)0, INUSE | MMAPD | PREVINUSE, meta_a);
	meta_c = set_meta(ptr_c, 12345, MMAPD, meta_b);

	mu_check(meta_a->size == 42);
	mu_check(meta_a->flags == 0x6);
	mu_check(meta_a->next == NULL);

	mu_check(meta_b->size == ~(size_t)0 >> 3);
	mu_check(meta_b->flags == 0x7);
	mu_check(meta_b->next == meta_a);

	mu_check(meta_c->size == 12345);
	mu_check(meta_c->flags == 0x2);
	mu_check(meta_c->next == meta_b);

	xfree(ptr_a);
	xfree(ptr_b);
	xfree(ptr_c);
}

MU_TEST(utils_test_get_payload)
{
	void	*ptr;
	void	*payload;

	ptr = xalloc();
	payload = get_payload(ptr);

	mu_check(payload == ptr + sizeof(t_meta));

	xfree(ptr);
}

MU_TEST_SUITE(utils_test_suite)
{
	MU_RUN_TEST(utils_test_size_alignment);
	MU_RUN_TEST(utils_test_set_meta);
	MU_RUN_TEST(utils_test_get_payload);
}

int utils_test()
{
	printf("Run utils test suite:\n");
	MU_RUN_SUITE(utils_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
