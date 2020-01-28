/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 10:38:08 by alngo             #+#    #+#             */
/*   Updated: 2020/01/28 17:24:44 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

#include "malloc.h"
#include "minunit.h"
#include <errno.h>

extern int errno;

int	utils_test();
int	malloc_test();
int free_test();

#endif
