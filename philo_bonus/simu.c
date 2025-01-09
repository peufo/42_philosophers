/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:12:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/08 01:30:06 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	terminate(t_simu *simu, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < simu->args.nb_philos)
	{
		kill(pids[i], SIGKILL);
		i++;
	}
	free(pids);
	sem_close(simu->forks);
	sem_close(simu->stop);
	printf("END OF SIMULATION\n");
}

static void	semaphores_init(t_simu *simu)
{
	sem_unlink(SIMU_FORKS);
	sem_unlink(SIMU_STOP);
	simu->forks = sem_open(SIMU_FORKS, O_CREAT, 0600, simu->args.nb_philos);
	simu->stop = sem_open(SIMU_STOP, O_CREAT, 0600, 0);
}

void	simu_start(t_simu *simu)
{
	int		i;
	pid_t	*pids;
	int		nb_philos;

	semaphores_init(simu);
	simu->start_at = get_time();
	nb_philos = simu->args.nb_philos;
	pids = malloc(sizeof(*pids) * nb_philos);
	i = 0;
	while (i < nb_philos)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			philo_start(simu, i + 1);
			exit(0);
		}
		i++;
	}
	sem_wait(simu->stop);
	terminate(simu, pids);
}
