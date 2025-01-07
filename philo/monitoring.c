/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:32:24 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/07 01:23:04 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	philo_died_in(t_philo *philo)
{
	int	eat_at;

	eat_at = client_get(philo->monit.eat_at);
	return ((eat_at + philo->args.time_to_die) - get_time());
}

static int	philos_are_running(t_philo *philos, int time_left, int nb_philos)
{
	int	i;
	int	died_in;
	int	nb_philos_end;

	nb_philos_end = 0;
	i = 0;
	while (i < nb_philos)
	{
		if (client_get(philos[i].monit.is_end))
		{
			nb_philos_end++;
			i++;
			continue ;
		}
		died_in = philo_died_in(philos + i);
		if (died_in < time_left)
			time_left = died_in;
		if (time_left < 0)
			return (put_state(philos + i, DIED), 0);
		i++;
	}
	if (nb_philos == nb_philos_end)
		return (0);
	usleep(1000 * (time_left + 1));
	return (1);
}

void	*monitoring(void *data)
{
	t_philo		*philos;
	int			nb_philos;
	int			time_to_die;
	t_client	simu_end;

	philos = (t_philo *)data;
	time_to_die = philos->args.time_to_die;
	nb_philos = philos->args.nb_philos;
	simu_end = philos->monit.simu_end;
	while (!client_get(simu_end))
		if (!philos_are_running(philos, time_to_die, nb_philos))
			return (client_set(simu_end, 1), NULL);
	return (NULL);
}