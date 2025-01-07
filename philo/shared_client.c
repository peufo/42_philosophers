/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_client.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 23:46:30 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/07 00:21:54 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_client	client_create(t_source *source)
{
	return ((t_client){
		.value = &(source->value),
		.mutex = &(source->mutex),
	});
}

void	client_set(t_client client, int value)
{
	pthread_mutex_lock(client.mutex);
	*(client.value) = value;
	pthread_mutex_unlock(client.mutex);
}

int	client_get(t_client client)
{
	int	value;

	pthread_mutex_lock(client.mutex);
	value = *(client.value);
	pthread_mutex_unlock(client.mutex);
	return (value);
}
