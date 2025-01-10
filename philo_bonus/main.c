/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:39:11 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/10 13:27:40 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	print_args_help(char *error)
{
	if (error)
	{
		printf("\033[1mError\033[0m\n");
		printf("%s\n\n", error);
	}
	printf("\033[1mUsage\033[0m\n");
	printf("./philo nb_philos time_to_die time_to_eat ");
	printf("time_to_sleep [max_times_eat]\n\n");
	printf("\033[1mExemple\033[0m\n");
	printf("./philo 4 4000 1000 1500\n\n");
	if (error)
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_simu	simu;
	int		i;

	if (ac < 5 || 6 < ac)
		return (print_args_help("Bad arguments count"));
	i = 1;
	while (i < ac)
		if (!ft_is_positive_int(av[i++]))
			return (print_args_help("An argument is not a positive int"));
	simu.args.nb_philos = ft_atoi(av[1]);
	simu.args.time_to_die = ft_atoi(av[2]);
	simu.args.time_to_eat = ft_atoi(av[3]);
	simu.args.time_to_sleep = ft_atoi(av[4]);
	simu.args.max_times_eat = -1;
	if (ac == 6)
		simu.args.max_times_eat = ft_atoi(av[5]);
	if (simu.args.nb_philos == 0)
		return (print_args_help("nb_philos need to be greater than 0"));
	simu_start(&simu);
	return (0);
}
