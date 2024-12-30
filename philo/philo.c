/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 00:06:13 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/30 20:05:54 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static int	take_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_mutex));
	if (philo->is_fork_used)
	{
		pthread_mutex_unlock(&(philo->fork_mutex));
		return (0);
	}
	philo->is_fork_used = 1;
	pthread_mutex_unlock(&(philo->fork_mutex));
	return (1);
}
static	void free_fork(t_philo *philo)
{
	pthread_mutex_lock(&(philo->fork_mutex));
	philo->is_fork_used = 0;
	pthread_mutex_unlock(&(philo->fork_mutex));
}

static int	await_forks(t_philo *philo)
{
	if (!take_fork(philo))
		return (1);
	if (!take_fork(philo->next))
	{
		free_fork(philo);
		return (1);
	}
	usleep(10000);
	printf("%d %d has taken a fork\n", get_time(), philo->index);
	printf("%d %d has taken a fork\n", get_time(), philo->index);
	return (0);
}

static int	philo_no_eat_duration(t_philo *philo)
{
	int	eat_at;

	pthread_mutex_lock(&(philo->eat_at_mutex));
	eat_at = philo->eat_at;
	pthread_mutex_unlock(&(philo->eat_at_mutex));
	return (get_time() - eat_at);
}

static void	philo_eat(t_philo *philo)
{
	printf("%d %d is eating\n", get_time(), philo->index);
	pthread_mutex_lock(&(philo->eat_at_mutex));
	philo->eat_at = get_time();
	pthread_mutex_unlock(&(philo->eat_at_mutex));
	usleep(philo->args.time_to_eat * 1000);
}

void	philo_cycle(t_philo *philo)
{
	printf("%d %d is thinking\n", get_time(), philo->index);
	while (await_forks(philo))
	{
		if (philo_no_eat_duration(philo) > philo->args.time_to_die)
		{
			printf("not_eat_duration %d\n", philo_no_eat_duration(philo));
			printf("%d %d  is died\n", get_time(), philo->index);
			return ;
		}
	}
	philo_eat(philo);
	printf("%d %d is sleeping\n", get_time(), philo->index);
	free_fork(philo);
	free_fork(philo->next);
	usleep(philo->args.time_to_sleep * 1000);
	//philo_cycle(philo);
}

void	*philo_start(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	philo->eat_at = get_time();
	philo_cycle(philo);
	return (NULL);
}
