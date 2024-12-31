/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:10:18 by jvoisard          #+#    #+#             */
/*   Updated: 2024/12/31 03:13:39 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*ft_strcpy(char *src, char *dest)
{
	while (*src)
		*(dest++) = *(src++);
	*dest = '\0';
	return (dest);
}

static char	*set_message(char msg[20], t_philo_state state)
{
	char	*text;
	char	*icon;

	text = (char [][20]){
	[SLEEP] = "is sleeping",
	[EAT] = "is eating",
	[THINK] = "is thinking",
	[DIED] = "is died",
	[TAKE_FORK] = "has taken a fork",
	}[state];
	icon = (char [][20]){
	[SLEEP] = "🛌",
	[EAT] = "🥣",
	[THINK] = "🧐",
	[DIED] = "💀",
	[TAKE_FORK] = "🥄",
	}[state];
	if (LOGS_MODE_PRETTY)
		return (ft_strcpy(icon, msg));
	else
		return (ft_strcpy(text, msg));
}

static int	philo_check_is_died(t_philo *philo)
{
	if (philo->is_died)
		return (1);
	philo->is_died = get_time() - philo->eat_at > philo->args.time_to_die;
	if (philo->is_died)
		return (put_state(philo, DIED));
	return (philo->is_died);
}

int	put_state(t_philo *philo, t_philo_state state)
{
	char	msg[100];
	char	*cursor;
	int		i;

	if (state != DIED && philo_check_is_died(philo))
		return (1);
	cursor = ft_strcpy("%-6d %d ", msg);
	if (LOGS_MODE_PRETTY)
	{
		i = 0;
		while (i++ < philo->id)
			cursor = ft_strcpy("   ", cursor);
	}
	cursor = set_message(cursor, state);
	*(cursor++) = '\n';
	*(cursor++) = '\0';
	pthread_mutex_lock(philo->put_lock);
	if (LOGS_MODE_PRETTY)
		printf(msg, get_time_relatif(), philo->id);
	else
		printf(msg, get_time(), philo->id);
	pthread_mutex_unlock(philo->put_lock);
	return (state == DIED);
}
