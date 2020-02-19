/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 10:38:08 by alngo             #+#    #+#             */
/*   Updated: 2020/02/13 13:31:04 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "malloc.h"
# include "minunit.h"
# include <errno.h>
# include <stdlib.h>

extern int errno;

int	utils_test();
int	malloc_test();
int realloc_test();
int free_test();
int show_alloc_mem_test();

#endif
