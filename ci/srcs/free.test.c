/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:55:07 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 16:31:23 by alngo            ###   ########.fr       */
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
	msync(meta_c, 5000, 0);
	mu_check(errno == ENOMEM);
}

MU_TEST(free_test_multiple_free)
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
	free(ptr_a);
	free(ptr_b);
	free(ptr_b);
	free(ptr_c);
	free(ptr_c);

	mu_check(meta_a->flags == 0x0);
	mu_check(meta_b->flags == 0x0);
	mu_check(munmap(ptr_c, 5000) == -1);
}

MU_TEST(free_test_prec_next_large)
{
	void	*ptr_a;
	void	*ptr_b;
	void	*ptr_c;

	t_meta	*meta_a;
	t_meta	*meta_b;
	t_meta	*meta_c;

	ptr_a = malloc(5000);
	ptr_b = malloc(5000);
	ptr_c = malloc(5000);

	meta_a = get_meta(ptr_a - sizeof(t_meta));
	meta_b = get_meta(ptr_b - sizeof(t_meta));
	meta_c = get_meta(ptr_c - sizeof(t_meta));

	mu_check(meta_b->next == meta_c);
	free(ptr_b);
	mu_check(meta_a->next == meta_c);
	mu_check(meta_c->next == NULL);
	free(ptr_c);
	mu_check(meta_a->next == NULL);
	free(ptr_a);
	mu_check(munmap(ptr_a, 5000) == -1);
}

MU_TEST_SUITE(free_test_suite)
{
	MU_RUN_TEST(free_test_invalid_pointer);
	MU_RUN_TEST(free_test_valid_pointer);
	MU_RUN_TEST(free_test_multiple_free);
	MU_RUN_TEST(free_test_prec_next_large);
}

int free_test()
{
	printf("Run free test suite:\n");
	MU_RUN_SUITE(free_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
