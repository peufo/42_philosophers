/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:36:23 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/28 11:34:45 by jvoisard         ###   ########.fr       */
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
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_times_eat;
	pthread_mutex_t	mutex;
}	t_args;

typedef enum e_philo_state
{
	SLEEP,
	EAT,
	THINK
}	t_philo_state;

typedef struct s_philo	t_philo;
struct s_philo
{
	int				index;
	pthread_mutex_t	fork_mutex;
	int				is_fork_used;
	t_philo_state	state;
	pthread_mutex_t	state_mutex;
	pthread_t		thread;
	t_args			*args;
	t_philo			*next;
};

int		ft_is_int(char *str);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	*run_philo(void *data);
void	eat(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);

#endif