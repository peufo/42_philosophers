/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:36:23 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/05 17:50:32 by jvoisard         ###   ########.fr       */
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
}	t_args;

typedef enum e_philo_state
{
	SLEEP,
	EAT,
	THINK,
	DIED,
	TAKE_FORK
}	t_philo_state;

typedef struct s_simu
{
	short			*is_running;
	pthread_mutex_t	*mutex;
}	t_simu;

typedef struct s_philo	t_philo;
struct s_philo
{
	int				id;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*put_lock;
	int				eat_at;
	int				is_died;
	pthread_t		thread;
	t_args			args;
	t_simu			simu;
};

int		ft_is_int(char *str);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	*philo_run(void *data);
int		philos_init(t_args *args);
void	philo_cycle(t_philo *philo);
int		get_time(void);
int		get_time_relatif(void);
int		put_state(t_philo *philo, t_philo_state state);

#endif