/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:36:23 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/31 00:43:28 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# define LOGS_MODE_PRETTY 1

typedef struct s_args
{
	int				nb_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_times_eat;
	int				time_to_priority;
}	t_args;

typedef enum e_philo_state
{
	SLEEP,
	EAT,
	THINK,
	DIED,
	TAKE
}	t_philo_state;


typedef struct s_philo	t_philo;
struct s_philo
{
	int				id;
	pthread_mutex_t	fork_mutex;
	int				is_fork_used;
	int				eat_at;
	pthread_t		thread;
	t_args			args;
	t_philo			*next;
};

int		ft_is_int(char *str);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	*philo_start(void *data);
void	philo_cycle(t_philo *philo);
int		get_time(void);
void	put(t_philo *philo, t_philo_state state);

#endif