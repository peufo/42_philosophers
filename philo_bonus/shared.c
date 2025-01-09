/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:05:30 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/09 16:04:36 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	shared_init(t_shared *shared, char *name, int value)
{
	shared->value = value;
	shared->ptr_value = &(shared->value);
	sem_unlink(name);
	shared->semaphore = sem_open(name, O_CREAT, 0600, true);
}

void	shared_destroy(t_shared *shared)
{
	sem_close(shared->semaphore);
}

void	shared_set(t_shared *shared, int value)
{
	sem_wait(shared->semaphore);
	*(shared->ptr_value) = value;
	sem_post(shared->semaphore);
}

int	shared_get(t_shared *shared)
{
	int	value;

	sem_wait(shared->semaphore);
	value = *(shared->ptr_value);
	sem_post(shared->semaphore);
	return (value);
}
