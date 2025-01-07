/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jonas.voisard@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 22:36:13 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/07 01:30:41 by jvoisard         ###   ########.fr       */
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

int	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	get_time_relatif(void)
{
	static int	start;

	if (!start)
		start = get_time();
	return (get_time() - start);
}

void	ft_sleep(int ms)
{
	int	start;

	start = get_time();
	while (start + ms > get_time())
		usleep(500);
}
