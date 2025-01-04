/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 13:33:13 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/04 13:49:54 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:39:11 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/04 13:25:11 by jvoisard         ###   ########.fr       */
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
			pthread_mutex_destroy(&(philos[i++].fork_left));
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
	int	i;
	int	nb_philos;

	i = 0;
	nb_philos = philos->args.nb_philos;
	while (i < nb_philos)
	{
		if (pthread_create(&(philos[i].thread), NULL, philo_run, &(philos[i])))
			return (terminate(philos, "Thread creation failed"));
		i++;
	}
	i = 0;
	while (i < nb_philos)
		pthread_join(philos[i++].thread, NULL);
	return (0);
}

static void	philos_link_forks(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->args.nb_philos - 1)
	{
		philos[i].fork_right = &(philos[i + 1].fork_left);
		i++;
	}
	philos[philos->args.nb_philos - 1].fork_right = &(philos->fork_left);
}

int	philos_init(t_args *args)
{
	int				i;
	t_philo			*philos;
	pthread_mutex_t	put_lock;

	philos = malloc(sizeof(*philos) * args->nb_philos);
	if (!philos)
		return (terminate(NULL, "Malloc failed"));
	pthread_mutex_init(&put_lock, NULL);
	i = 0;
	while (i < args->nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].args = *args;
		philos[i].eat_at = 0;
		philos[i].is_died = 0;
		philos[i].put_lock = &put_lock;
		pthread_mutex_init(&(philos[i].fork_left), NULL);
		i++;
	}
	philos_link_forks(philos);
	philos_start(philos);
	return (terminate(philos, NULL));
}
