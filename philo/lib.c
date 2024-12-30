/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:36:13 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/31 00:36:49 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_strcpy(char *src, char *dest)
{
	while (*src)
		*(dest++) = *(src++);
	*dest = '\0';
}

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static void	set_message(char msg[20], t_philo_state state)
{
	char	*text;
	char	*icon;

	text = (char [][20]){
	[SLEEP] = "is sleeping",
	[EAT] = "is eating",
	[THINK] = "is thinking",
	[DIED] = "is died",
	[TAKE] = "has taken a fork",
	}[state];
	icon = (char [][20]){
	[SLEEP] = "🛌",
	[EAT] = "🥣",
	[THINK] = "🧐",
	[DIED] = "💀",
	[TAKE] = "🥄",
	}[state];
	if (LOGS_MODE_PRETTY)
		ft_strcpy(icon, msg);
	else
		ft_strcpy(text, msg);
}

void put(t_philo *philo, t_philo_state state)
{
	char	msg[20];
	int		i;

	i = 0;
	set_message(msg, state);
	printf("%d %d ", get_time(), philo->id);
	if (LOGS_MODE_PRETTY)
		while (i < philo->id)
		{
			printf("\t");
			i++;
		}
	printf("%s\n", msg);
}
