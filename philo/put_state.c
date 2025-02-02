/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_state.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 01:10:18 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/09 14:57:59 by jvoisard         ###   ########.fr       */
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

int	put_state(t_philo *philo, t_philo_state state)
{
	char	msg[100];
	char	*cursor;
	int		i;

	if (state != DIED && shared_get(&(philo->simu_end)))
		return (0);
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
	return (1);
}
