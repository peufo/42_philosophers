/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:36:23 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/07 01:05:15 by jvoisard         ###   ########.fr       */
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
	pthread_mutex_t	*mutex;
	short			*is_end;
}	t_simu;

typedef struct s_source
{
	int				value;
	pthread_mutex_t	mutex;
}	t_source;

typedef struct s_client
{
	int				*value;
	pthread_mutex_t	*mutex;
}	t_client;

typedef struct s_monit
{
	t_client	eat_at;
	t_client	is_end;
	t_client	simu_end;
}	t_monit;

typedef struct s_philo	t_philo;
struct s_philo
{
	int				id;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*put_lock;
	t_client		simu_end;
	t_source		eat_at;
	t_source		is_end;
	int				is_died;
	pthread_t		thread;
	t_args			args;
	t_monit			monit;
};

int			ft_is_int(char *str);
int			ft_atoi(const char *str);
int			ft_strlen(char *str);
void		*monitoring(void *data);
void		*philo_run(void *data);
int			philos_init(t_args *args);
void		philo_cycle(t_philo *philo);
int			get_time(void);
int			get_time_relatif(void);
int			put_state(t_philo *philo, t_philo_state state);

void		source_init(t_source *source, int value);
void		source_set(t_source *source, int value);
int			source_get(t_source *source);
t_client	client_create(t_source *source);
void		client_set(t_client client, int value);
int			client_get(t_client client);

#endif