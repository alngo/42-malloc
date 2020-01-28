/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 10:39:42 by alngo             #+#    #+#             */
/*   Updated: 2020/01/28 11:20:08 by alngo            ###   ########.fr       */
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

	mu_check(meta_a->data == 0x156);
	mu_check(meta_b->data == ~(size_t)0);
	mu_check(meta_b->next == meta_a);
	mu_check(meta_c->data == 0x181CA);
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
	MU_RUN_SUITE(utils_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
