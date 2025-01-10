/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 00:12:57 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/10 12:43:03 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	terminate(t_simu *simu, pid_t *pids, char *error, bool kill_pids)
{
	int	i;

	i = 0;
	if (kill_pids)
	{
		while (i < simu->args.nb_philos)
		{
			kill(pids[i], SIGKILL);
			i++;
		}
	}
	free(pids);
	sem_close(simu->forks);
	sem_close(simu->end);
	sem_close(simu->put);
	if (error)
	{
		printf("Error: %s\n", error);
		exit(1);
	}
	exit(0);
}

static void	semaphores_init(t_simu *simu)
{
	sem_unlink(SIMU_FORKS);
	sem_unlink(SIMU_PUT);
	sem_unlink(SIMU_END);
	simu->forks = sem_open(SIMU_FORKS, O_CREAT, 0600, simu->args.nb_philos);
	simu->put = sem_open(SIMU_PUT, O_CREAT, 0600, true);
	simu->end = sem_open(SIMU_END, O_CREAT, 0600, false);
}

static void	wait_end(t_simu *simu)
{
	int	i;

	i = 0;
	while (i < simu->args.nb_philos)
	{
		sem_wait(simu->end);
		i++;
	}
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
	if (!pids)
		terminate(simu, pids, "Malloc failed", false);
	memset(pids, 0, sizeof(*pids) * nb_philos);
	i = 0;
	while (i < nb_philos)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			philo_start(simu, i + 1);
			return (terminate(simu, pids, NULL, false));
		}
		i++;
	}
	wait_end(simu);
	terminate(simu, pids, NULL, true);
}
