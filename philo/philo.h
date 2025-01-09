/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:36:23 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/09 15:41:19 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h> 
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

typedef struct s_shared
{
	pthread_mutex_t	mutex;
	pthread_mutex_t	*ptr_mutex;
	int				value;
	int				*ptr_value;
}	t_shared;

typedef struct s_philo	t_philo;
struct s_philo
{
	int				id;
	pthread_mutex_t	fork_left;
	pthread_mutex_t	*fork_right;
	pthread_mutex_t	*put_lock;
	t_shared		simu_end;
	t_shared		eat_at;
	t_shared		is_end;
	pthread_t		thread;
	t_args			args;
};

void		*monitoring(void *data);
void		*philo_run(void *data);

int			philos_init(t_args *args);
int			put_state(t_philo *philo, t_philo_state state);

void		shared_init(t_shared *shared, int value);
void		shared_destroy(t_shared *shared);
void		shared_set(t_shared *shared, int value);
int			shared_get(t_shared *shared);

int			get_time(void);
int			get_time_relatif(void);
int			ft_is_int(char *str);
int			ft_atoi(const char *str);
int			ft_strlen(char *str);
void		ft_sleep(int ms);

#endif