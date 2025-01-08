/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:00:27 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/08 01:21:13 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_cycle(t_philo *philo)
{
	while (1)
	{
		put_state(philo, THINK);
		sem_wait(philo->simu->forks);
		put_state(philo, TAKE_FORK);
		sem_wait(philo->simu->forks);
		put_state(philo, TAKE_FORK);
		put_state(philo, EAT);
		philo->eat_at = get_time();
		ft_sleep(philo->simu->args.time_to_eat);
		put_state(philo, SLEEP);
		sem_post(philo->simu->forks);
		sem_post(philo->simu->forks);
		ft_sleep(philo->simu->args.time_to_sleep);
		if (!(--philo->simu->args.max_times_eat))
		{
			sem_post(philo->simu->stop);
			return ;
		}
	}
}

void	philo_start(t_simu *simu, int id)
{
	t_philo	philo;
	
	(void)simu;
	philo.id = id;
	philo.simu = simu;
	philo_cycle(&philo);
}
