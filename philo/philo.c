/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 00:06:13 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/09 14:46:12 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	await_forks(t_philo *philo)
{
	pthread_mutex_t	*fork_a;
	pthread_mutex_t	*fork_b;

	if (philo->id % 2)
	{
		fork_a = &(philo->fork_left);
		fork_b = philo->fork_right;
	}
	else
	{
		fork_b = &(philo->fork_left);
		fork_a = philo->fork_right;
	}
	pthread_mutex_lock(fork_a);
	if (!put_state(philo, TAKE_FORK))
		return (pthread_mutex_unlock(fork_a), 0);
	pthread_mutex_lock(fork_b);
	if (!put_state(philo, TAKE_FORK))
	{
		pthread_mutex_unlock(fork_a);
		pthread_mutex_unlock(fork_b);
		return (0);
	}
	return (1);
}

static int	philo_eat(t_philo *philo)
{
	if (!await_forks(philo))
		return (0);
	if (!put_state(philo, EAT))
	{
		pthread_mutex_unlock(&(philo->fork_left));
		pthread_mutex_unlock(philo->fork_right);
		return (0);
	}
	shared_set(philo->eat_at, get_time());
	ft_sleep(philo->args.time_to_eat);
	return (1);
}

static void	philo_cycle(t_philo *philo)
{
	while (1)
	{
		if (!put_state(philo, THINK))
			return ;
		if (!philo_eat(philo))
			return ;
		put_state(philo, SLEEP);
		pthread_mutex_unlock(&(philo->fork_left));
		pthread_mutex_unlock(philo->fork_right);
		ft_sleep(philo->args.time_to_sleep);
		if (!(--philo->args.max_times_eat))
		{
			shared_set(philo->is_end, 1);
			return ;
		}
	}
}

void	*philo_run(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	shared_set(philo->eat_at, get_time());
	philo_cycle(philo);
	return (NULL);
}
