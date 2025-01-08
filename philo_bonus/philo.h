/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:36:23 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/08 01:21:46 by jvoisard         ###   ########.fr       */
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

typedef struct s_simu
{
	sem_t	*forks;
	sem_t	*stop;
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
	t_simu		*simu;
	pthread_t	dead_thread;
}	t_philo;

void	simu_start(t_simu *simu);
void	philo_start(t_simu *simu, int id);
void	put_state(t_philo *philo, t_philo_state state);

void	*monitoring(void *data);
void	*philo_run(void *data);
int		philos_init(t_args *args);

int		get_time(void);
int		get_time_relatif(void);
int		ft_is_int(char *str);
int		ft_atoi(const char *str);
int		ft_strlen(char *str);
void	ft_sleep(int ms);

#endif