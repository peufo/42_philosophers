/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:33:13 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/07 01:25:41 by jvoisard         ###   ########.fr       */
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
			pthread_mutex_destroy(&(philos[i].eat_at.mutex));
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

	nb_philos = philos->args.nb_philos;
	i = 0;
	while (i < nb_philos)
	{
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
	t_source *simu_end
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
		philos[i].is_died = 0;
		philos[i].put_lock = put_lock;
		source_init(&(philos[i].eat_at), 0);
		philos[i].monit.eat_at = client_create(&(philos[i].eat_at));
		source_init(&(philos[i].is_end), 0);
		philos[i].monit.is_end = client_create(&(philos[i].is_end));
		philos[i].simu_end = client_create(simu_end);
		philos[i].monit.simu_end = client_create(simu_end);
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
	t_source		simu_end;

	philos = malloc(sizeof(*philos) * args->nb_philos);
	if (!philos)
		return (terminate(NULL, "Malloc failed"));
	pthread_mutex_init(&put_lock, NULL);
	source_init(&simu_end, 0);
	philos_init_values(philos, args, &put_lock, &simu_end);
	philos_start(philos);
	return (terminate(philos, NULL));
}
