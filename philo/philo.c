/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 00:06:13 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/28 02:11:11 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_time(void)
{
	struct	timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static void	eat(t_philo *philo)
{
	printf("%d %d has taken a fork\n", get_time(), philo->index);

}

static void	philo_sleep(t_philo *philo)
{
	int	time_to_sleep;

	pthread_mutex_lock(&(philo->args->mutex));
	time_to_sleep = philo->args->time_to_sleep;
	pthread_mutex_unlock(&(philo->args->mutex));

	printf("%d %d is sleeping\n", get_time(), philo->index);
	usleep(time_to_sleep * 1000);
	eat(philo);
}

//timestamp_in_ms X has taken a fork
void	*run_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo_sleep(philo);
	/*
	printf("%d %d  is eating\n", get_time(), philo->index);
	printf("%d %d  is thinking\n", get_time(), philo->index);
	printf("%d %d  is died\n", get_time(), philo->index);
	*/
	return (NULL);
}
