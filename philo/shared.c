/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:05:30 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/09 15:02:10 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	shared_init(t_shared *shared, int value)
{
	shared->value = value;
	shared->ptr_value = &(shared->value);
	pthread_mutex_init(&(shared->mutex), NULL);
	shared->ptr_mutex = &(shared->mutex);
}

void	shared_destroy(t_shared *shared)
{
	pthread_mutex_destroy(shared->ptr_mutex);
}

void	shared_set(t_shared *shared, int value)
{
	pthread_mutex_lock(shared->ptr_mutex);
	*(shared->ptr_value) = value;
	pthread_mutex_unlock(shared->ptr_mutex);
}

int	shared_get(t_shared *shared)
{
	int	value;

	pthread_mutex_lock(shared->ptr_mutex);
	value = *(shared->ptr_value);
	pthread_mutex_unlock(shared->ptr_mutex);
	return (value);
}
