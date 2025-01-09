/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:36:23 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/09 13:25:23 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h> 
# define LOGS_MODE_PRETTY 1
# define SIMU_FORKS "simu_forks"
# define SIMU_STOP "simu_stop"

typedef struct s_args
{
	int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_times_eat;
}	t_args;

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

typedef struct s_simu
{
	int		start_at;
	sem_t	*stop;
	sem_t	*forks;
	t_args	args;
}	t_simu;

typedef enum e_philo_state
{
	SLEEP,
	EAT,
	THINK,
	DIED,
	TAKE_FORK
}	t_philo_state;

typedef struct s_philo
{
	int			id;
	int			eat_at;
	t_source	died_at;
	t_client	died_at_monit;
	t_source	is_end;
	t_client	is_end_monit;
	t_simu		*simu;
	pthread_t	dead_thread;
}	t_philo;

void		simu_start(t_simu *simu);
void		philo_start(t_simu *simu, int id);
void		put_state(t_philo *philo, t_philo_state state);

void		*monitoring(void *data);
void		*philo_run(void *data);
int			philos_init(t_args *args);

void		source_init(t_source *source, int value);
void		source_set(t_source *source, int value);
int			source_get(t_source *source);
t_client	client_create(t_source *source);
void		client_set(t_client client, int value);
int			client_get(t_client client);

int			get_time(void);
int			get_time_relatif(t_simu *simu);
int			ft_is_int(char *str);
int			ft_atoi(const char *str);
int			ft_strlen(char *str);
void		ft_sleep(int ms);

#endif