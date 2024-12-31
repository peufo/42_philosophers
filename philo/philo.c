/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 00:06:13 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/31 02:44:55 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	await_forks(t_philo *philo)
{
	pthread_mutex_t	*fork_a;
	pthread_mutex_t	*fork_b;

	if (philo->id % 2)
	{
		fork_a = &(philo->fork);
		fork_b = &(philo->next->fork);
	}
	else
	{
		fork_b = &(philo->fork);
		fork_a = &(philo->next->fork);
	}
	pthread_mutex_lock(fork_a);
	if (put_state(philo, TAKE_FORK))
		return (pthread_mutex_unlock(fork_a), 1);
	pthread_mutex_lock(fork_b);
	if (put_state(philo, TAKE_FORK))
		return (pthread_mutex_unlock(fork_b), 1);
	return (0);
}

void	philo_cycle(t_philo *philo)
{
	while (1)
	{
		put_state(philo, THINK);
		if (await_forks(philo))
			return ;
		put_state(philo, EAT);
		philo->eat_at = get_time();
		usleep(philo->args.time_to_eat * 1000);
		put_state(philo, SLEEP);
		pthread_mutex_unlock(&(philo->fork));
		pthread_mutex_unlock(&(philo->next->fork));
		usleep(philo->args.time_to_sleep * 1000);
		if (!(--philo->args.max_times_eat))
			return ;
	}
}

void	*philo_run(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->eat_at = get_time();
	philo_cycle(philo);
	printf("END OF %d\n", philo->id);
	return (NULL);
}
