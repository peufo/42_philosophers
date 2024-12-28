/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:36:23 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/28 01:08:32 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_args
{
	int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_times_eat;
}	t_args;

typedef enum e_philo_state
{
	SLEEP,
	EAT,
	THINK
}	t_philo_state;

typedef struct s_philo
{
	int				index;
	t_philo_state	state;
	t_args			*args;
	pthread_t		thread;
}	t_philo;

int		ft_is_int(char *str);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	*run_philo(void *data);

#endif