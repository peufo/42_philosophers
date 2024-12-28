/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:39:11 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/28 02:07:27 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	terminate(t_philo *philos, char *error)
{
	if (philos)
	{
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
	printf("./philo 4 1000 1000 1000\n\n");
	return (0);
}

static t_philo	*create_philos(t_args *args)
{
	int			i;
	t_philo		*philos;

	i = 0;
	philos = malloc(sizeof(*philos) * args->nb_philos);
	if (!philos)
		return (terminate(NULL, "Malloc failed"), NULL);
	while (i < args->nb_philos)
	{
		philos[i].index = i + 1;
		philos[i].args = args;
		philos[i].state = SLEEP;
		pthread_mutex_init(&(philos[i].fork_mutex), NULL);
		pthread_mutex_init(&(philos[i].state_mutex), NULL);
		philos[i].left = philos - 1;
		philos[i].right = philos + 1;
		//if (i == 0)
		//	philos[i].left += args->nb_philos;
		//if (i == args->nb_philos - 1)
		//	philos[i].right = philos;
		if (pthread_create(&(philos[i].thread), NULL, run_philo, philos + i))
			return (terminate(philos, "Thread creation failed"), NULL);
		pthread_detach(philos[i].thread);
		i++;
	}
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
			return (print_args_help("An argument is not an interger"));
	args.nb_philos = ft_atoi(av[1]);
	args.time_to_die = ft_atoi(av[2]);
	args.time_to_eat = ft_atoi(av[3]);
	args.time_to_sleep = ft_atoi(av[4]);
	args.max_times_eat = -1;
	pthread_mutex_init(&(args.mutex), NULL);
	if (ac == 6)
		args.max_times_eat = ft_atoi(av[5]);
	philos = create_philos(&args);
	if (!philos)
		return (1);
}
