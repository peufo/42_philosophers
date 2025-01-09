/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_source.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 00:05:30 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/09 14:20:51 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	source_init(t_source *source, int value)
{
	source->value = value;
	pthread_mutex_init(&(source->mutex), NULL);
}

void	source_set(t_source *source, int value)
{
	pthread_mutex_lock(&(source->mutex));
	source->value = value;
	pthread_mutex_unlock(&(source->mutex));
}

int	source_get(t_source *source)
{
	int	value;

	pthread_mutex_lock(&(source->mutex));
	value = source->value;
	pthread_mutex_unlock(&(source->mutex));
	return (value);
}
