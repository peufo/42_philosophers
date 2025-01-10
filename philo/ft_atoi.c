/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvoisard <jvoisard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 23:31:41 by jvoisard          #+#    #+#             */
/*   Updated: 2025/01/10 13:16:04 by jvoisard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	is_space(char c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n'
		|| c == '\v'
		|| c == '\f'
		|| c == '\r');
}

static int	is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

static int	ft_is_over(char *str, char *limit)
{
	int		limit_len;
	int		str_len;

	limit_len = ft_strlen(limit);
	str_len = ft_strlen(str);
	if (str_len < limit_len)
		return (0);
	if (str_len > limit_len)
		return (1);
	while (*limit)
	{
		if (*str > *limit)
			return (1);
		if (*str < *limit)
			return (0);
		str++;
		limit++;
	}
	return (0);
}

int	ft_is_positive_int(char *str)
{
	short	sign;

	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign -= (*(str++) == '-') * 2;
	if (sign == -1)
		return (0);
	while (*str == '0')
		str++;
	if (ft_is_over(str, "2147483647"))
		return (0);
	while (*str)
		if (!is_digit(*(str++)))
			return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		n;
	short	sign;

	n = 0;
	sign = 1;
	while (is_space(*str))
		str++;
	if (*str == '-' || *str == '+')
		sign -= (*(str++) == '-') * 2;
	while (*str == '0')
		str++;
	while (is_digit(*str))
		n = n * 10 + sign * (*(str++) - '0');
	return (n);
}
