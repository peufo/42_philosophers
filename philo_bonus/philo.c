/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:00:27 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/09 17:45:00 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	kill_all(t_philo	*philo)
{
	int	i;

	i = 0;
	while (i < philo->simu->args.nb_philos)
	{
		sem_post(philo->simu->end);
		i++;
	}
}

static void	*dead_monitoring(void *data)
{
	t_philo	*philo;
	int		time_left;

	philo = (t_philo *)data;
	(void)philo;
	while (!shared_get(&(philo->is_end)))
	{
		time_left = shared_get(&(philo->died_at)) - get_time();
		if (time_left < 0)
		{
			shared_set(&(philo->is_end), true);
			put_state(philo, DIED);
			kill_all(philo);
			return (NULL);
		}
		ft_sleep(time_left + 1);
	}
	return (NULL);
}

static void	philo_cycle(t_philo *philo)
{
	int	time_to_die;

	time_to_die = philo->simu->args.time_to_die;
	while (!shared_get(&(philo->is_end)))
	{
		put_state(philo, THINK);
		sem_wait(philo->simu->forks);
		put_state(philo, TAKE_FORK);
		sem_wait(philo->simu->forks);
		put_state(philo, TAKE_FORK);
		put_state(philo, EAT);
		shared_set(&(philo->died_at), get_time() + time_to_die);
		ft_sleep(philo->simu->args.time_to_eat);
		sem_post(philo->simu->forks);
		sem_post(philo->simu->forks);
		put_state(philo, SLEEP);
		ft_sleep(philo->simu->args.time_to_sleep);
		if (!(--philo->simu->args.max_times_eat))
		{
			shared_set(&(philo->is_end), true);
			sem_post(philo->simu->end);
			return ;
		}
	}
}

void	philo_start(t_simu *simu, int id)
{
	t_philo	philo;
	int		died_at;

	philo.id = id;
	philo.simu = simu;
	died_at = get_time() + philo.simu->args.time_to_die;
	shared_init(&(philo.died_at), "SEM_PHILO_DIED_AT", died_at);
	shared_init(&(philo.is_end), "SEM_PHILO_IS_END", false);
	pthread_create(&(philo.dead_thread), NULL, dead_monitoring, &philo);
	pthread_detach(philo.dead_thread);
	philo_cycle(&philo);
	shared_destroy(&(philo.died_at));
	shared_destroy(&(philo.is_end));
}
