/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:39:11 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/31 03:06:16 by jvoisard         ###   ########.fr       */
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
			pthread_mutex_destroy(&(philos[i++].fork));
		pthread_mutex_destroy(philos->put_lock);
		free(philos);
	}
	if (!error)
		return (0);
	printf("Error: %s\n", error);
	return (1);
}

static int	print_args_help(char *error)
{
	printf("Error: %s\n\n", error);
	printf("Usage:\n");
	printf("./philo nb_philos time_to_die time_to_eat ");
	printf("time_to_sleep [max_times_eat]\n\n");
	printf("Exemple:\n");
	printf("./philo 4 4000 1000 1500\n\n");
	return (0);
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

static t_philo	*philos_create(t_args *args)
{
	int				i;
	t_philo			*philos;
	pthread_mutex_t	put_lock;

	i = 0;
	philos = malloc(sizeof(*philos) * args->nb_philos);
	if (!philos)
		return (terminate(NULL, "Malloc failed"), NULL);
	pthread_mutex_init(&put_lock, NULL);
	while (i < args->nb_philos)
	{
		philos[i].id = i + 1;
		philos[i].args = *args;
		philos[i].eat_at = 0;
		philos[i].put_lock = &put_lock;
		pthread_mutex_init(&(philos[i].fork), NULL);
		philos[i].next = philos + i + 1;
		if (i == args->nb_philos - 1)
			philos[i].next = philos;
		i++;
	}
	philos_start(philos);
	return (philos);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	*philos;
	int		i;

	if (ac < 5 || 6 < ac)
		return (print_args_help("Bad arguments count"));
	i = 1;
	while (i < ac)
		if (!ft_is_int(av[i++]))
			return (print_args_help("An argument is not an int"));
	args.nb_philos = ft_atoi(av[1]);
	args.time_to_die = ft_atoi(av[2]);
	args.time_to_eat = ft_atoi(av[3]);
	args.time_to_sleep = ft_atoi(av[4]);
	args.max_times_eat = -1;
	if (ac == 6)
		args.max_times_eat = ft_atoi(av[5]);
	philos = philos_create(&args);
	if (!philos)
		return (1);
	terminate(philos, NULL);
}
