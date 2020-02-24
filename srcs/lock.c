/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alngo <alngo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 09:13:48 by alngo             #+#    #+#             */
/*   Updated: 2020/02/20 09:20:05 by alngo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

pthread_mutex_t		g_lock;

int					init_lock(void)
{
	if (pthread_mutex_init(&g_lock, NULL) != 0)
		return (1);
	return (0);
}

void				lock(void)
{
	if (!init_lock())
	{
		pthread_mutex_lock(&g_lock);
	}
}

void				unlock(void)
{
	if (!init_lock())
	{
		pthread_mutex_unlock(&g_lock);
	}
}
