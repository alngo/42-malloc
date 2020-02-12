/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 14:50:22 by alngo             #+#    #+#             */
/*   Updated: 2020/02/10 16:47:11 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(int argc, char *argv[])
{
	utils_test();
	malloc_test();
	free_test();
	realloc_test();
	show_alloc_mem_test();
	return (MU_EXIT_CODE);
}
