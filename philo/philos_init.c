/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:33:13 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/09 15:13:42 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	terminate(t_philo *philos, char *error)
{
	int	i;

	if (philos)
	{
		i = 0;
		while (i < philos->args.nb_philos)
		{
			shared_destroy(&(philos[i].eat_at));
			shared_destroy(&(philos[i].is_end));
			pthread_mutex_destroy(&(philos[i].fork_left));
			i++;
		}
		pthread_mutex_destroy(philos->put_lock);
		free(philos);
	}
	if (!error)
		return (0);
	printf("Error: %s\n", error);
	return (1);
}

static int	philos_start(t_philo *philos)
{
	int			i;
	int			nb_philos;
	pthread_t	monit;
	int			start_time;

	nb_philos = philos->args.nb_philos;
	start_time = get_time();
	i = 0;
	while (i < nb_philos)
	{
		shared_set(&(philos[i].eat_at), start_time);
		if (pthread_create(&(philos[i].thread), NULL, philo_run, philos + i))
			return (terminate(philos, "Create thread philo failed"));
		i++;
	}
	if (pthread_create(&monit, NULL, monitoring, philos))
		return (terminate(philos, "Create thread monitoring failed"));
	pthread_join(monit, NULL);
	i = 0;
	while (i < nb_philos)
		pthread_join(philos[i++].thread, NULL);
	return (0);
}

static void	philos_init_values(
	t_philo *philos,
	t_args *args,
	pthread_mutex_t *put_lock,
	t_shared simu_end
)
{
	int	i;
	int	nb_philos;

	nb_philos = args->nb_philos;
	i = 0;
	while (i < nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].args = *args;
		philos[i].put_lock = put_lock;
		shared_init(&(philos[i].eat_at), 0);
		shared_init(&(philos[i].is_end), 0);
		philos[i].simu_end = simu_end;
		pthread_mutex_init(&(philos[i].fork_left), NULL);
		if (i < nb_philos - 1)
			philos[i].fork_right = &(philos[i + 1].fork_left);
		else
			philos[nb_philos - 1].fork_right = &(philos->fork_left);
		i++;
	}
}

int	philos_init(t_args *args)
{
	t_philo			*philos;
	pthread_mutex_t	put_lock;
	t_shared		simu_end;

	philos = malloc(sizeof(*philos) * args->nb_philos);
	if (!philos)
		return (terminate(NULL, "Malloc failed"));
	pthread_mutex_init(&put_lock, NULL);
	shared_init(&simu_end, 0);
	philos_init_values(philos, args, &put_lock, simu_end);
	philos_start(philos);
	shared_destroy(&simu_end);
	return (terminate(philos, NULL));
}
