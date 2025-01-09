/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:36:23 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/09 15:52:42 by jvoisard         ###   ########.fr       */
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
# include <string.h>
# define LOGS_MODE_PRETTY 1
# define SIMU_FORKS "sem_simu_forks"
# define SIMU_END "sem_simu_end"

typedef struct s_args
{
	int	nb_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_times_eat;
}	t_args;

typedef struct s_shared
{
	sem_t	*semaphore;
	int		value;
	int		*ptr_value;
}	t_shared;

typedef struct s_simu
{
	int		start_at;
	sem_t	*end;
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
	t_shared	died_at;
	t_shared	is_end;
	t_simu		*simu;
	pthread_t	dead_thread;
}	t_philo;

void		simu_start(t_simu *simu);
void		philo_start(t_simu *simu, int id);
void		put_state(t_philo *philo, t_philo_state state);

void		shared_init(t_shared *shared, char *name, int value);
void		shared_destroy(t_shared *shared);
void		shared_set(t_shared *shared, int value);
int			shared_get(t_shared *shared);

int			get_time(void);
int			get_time_relatif(t_simu *simu);
int			ft_is_int(char *str);
int			ft_atoi(const char *str);
int			ft_strlen(char *str);
void		ft_sleep(int ms);

#endif