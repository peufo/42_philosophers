/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 00:06:13 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/28 12:44:21 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	await_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_mutex));
	if (philo->next->is_fork_used)
	{
		pthread_mutex_unlock(&(philo->fork_mutex));
		return (1);
	}
	pthread_mutex_lock(&(philo->next->fork_mutex));
	philo->is_fork_used = 1;
	philo->next->is_fork_used = 1;
	printf("%d %d has taken a fork\n", get_time(), philo->index);
	printf("%d %d has taken a fork\n", get_time(), philo->index);
	return (0);
}

void	philo_eat(t_philo *philo)
{
	int	time_to_eat;

	printf("%d %d is thinking\n", get_time(), philo->index);
	while (await_forks(philo))
		;
	pthread_mutex_lock(&(philo->args->mutex));
	time_to_eat = philo->args->time_to_eat;
	pthread_mutex_unlock(&(philo->args->mutex));
	printf("%d %d is eating\n", get_time(), philo->index);
	usleep(time_to_eat * 1000);
	philo->is_fork_used = 0;
	philo->next->is_fork_used = 0;
	pthread_mutex_unlock((&philo->fork_mutex));
	pthread_mutex_unlock((&philo->next->fork_mutex));
	philo_sleep(philo);
}

void	philo_sleep(t_philo *philo)
{
	int	time_to_sleep;

	pthread_mutex_lock(&(philo->args->mutex));
	time_to_sleep = philo->args->time_to_sleep;
	pthread_mutex_unlock(&(philo->args->mutex));
	printf("%d %d is sleeping\n", get_time(), philo->index);
	usleep(time_to_sleep * 1000);
	philo_eat(philo);
}

//printf("%d %d  is died\n", get_time(), philo->index);
void	*run_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo_sleep(philo);
	return (NULL);
}
