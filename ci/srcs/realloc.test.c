/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:03:54 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 16:36:13 by alngo            ###   ########.fr       */
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

	meta_a = meta(ptr_a - sizeof(t_meta));
	meta_b = meta(ptr_b - sizeof(t_meta));

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

	meta_a = meta(ptr_a - sizeof(t_meta));
	meta_b = meta(ptr_b - sizeof(t_meta));

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
	MU_RUN_TEST(realloc_test_large_payload);
	MU_RUN_TEST(realloc_test_large_to_tiny);
}

int realloc_test()
{
	printf("Run realloc test suite:\n");
	MU_RUN_SUITE(realloc_test_suite);
	MU_REPORT();
	return MU_EXIT_CODE;
}
