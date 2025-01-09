/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:00:27 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/09 13:34:25 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*dead_monitoring(void *data)
{
	t_philo	*philo;
	int		time_left;

	philo = (t_philo *)data;
	(void)philo;
	while (!client_get(philo->is_end_monit))
	{
		time_left = client_get(philo->died_at_monit) - get_time();
		printf("time_left %d\n", time_left);
		if (time_left < 0)
		{
			client_set(philo->is_end_monit, true);
			put_state(philo, DIED);
			return (NULL);
		}
		ft_sleep(time_left + 1);
	}
	return (NULL);
}

void	philo_cycle(t_philo *philo)
{
	int	time_to_die;

	time_to_die = philo->simu->args.time_to_die;
	while (!source_get(&(philo->is_end)))
	{
		put_state(philo, THINK);
		sem_wait(philo->simu->forks);
		put_state(philo, TAKE_FORK);
		sem_wait(philo->simu->forks);
		put_state(philo, TAKE_FORK);
		put_state(philo, EAT);
		source_set(&(philo->died_at), get_time() + time_to_die);
		ft_sleep(philo->simu->args.time_to_eat);
		put_state(philo, SLEEP);
		sem_post(philo->simu->forks);
		sem_post(philo->simu->forks);
		ft_sleep(philo->simu->args.time_to_sleep);
		if (!(--philo->simu->args.max_times_eat))
		{
			source_set(&(philo->is_end), true);
			return ;
		}
	}
}

void	philo_start(t_simu *simu, int id)
{
	t_philo	philo;

	philo.id = id;
	philo.simu = simu;
	source_init(&(philo.died_at), get_time() + philo.simu->args.time_to_die);
	source_init(&(philo.is_end), false);
	philo.died_at_monit = client_create(&(philo.died_at));
	philo.is_end_monit = client_create(&(philo.is_end));
	pthread_create(&(philo.dead_thread), NULL, dead_monitoring, &philo);
	philo_cycle(&philo);
}
