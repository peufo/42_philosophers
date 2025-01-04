/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:39:11 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/04 13:40:43 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	main(int ac, char **av)
{
	t_args	args;
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
	return (philos_init(&args));
}
