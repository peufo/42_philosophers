/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 00:06:13 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/31 00:34:21 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	await_forks(t_philo *philo)
{
	pthread_mutex_t	*fork_a;
	pthread_mutex_t	*fork_b;

	if (philo->id % 2)
	{
		fork_a = &(philo->fork_mutex);
		fork_b = &(philo->next->fork_mutex);
	}
	else
	{
		fork_b = &(philo->fork_mutex);
		fork_a = &(philo->next->fork_mutex);
	}
	pthread_mutex_lock(fork_a);
	put(philo, TAKE);
	pthread_mutex_lock(fork_b);
	put(philo, TAKE);
	return (0);
}

static void free_fork(t_philo *philo)
{
	pthread_mutex_unlock(&(philo->fork_mutex));
}

void	philo_cycle(t_philo *philo)
{
	while (1)
	{
		put(philo, THINK);
		await_forks(philo);
		if (get_time() - philo->eat_at > philo->args.time_to_die)
		{
			put(philo, DIED);
			free_fork(philo);
			free_fork(philo->next);
			return ;
		}
		put(philo, EAT);
		philo->eat_at = get_time();
		usleep(philo->args.time_to_eat * 1000);
		put(philo, SLEEP);
		free_fork(philo);
		free_fork(philo->next);
		usleep(philo->args.time_to_sleep * 1000);
		if (!(--philo->args.max_times_eat))
			return ;
	}
}

void	*philo_start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->eat_at = get_time();
	philo_cycle(philo);
	return (NULL);
}
