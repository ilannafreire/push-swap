/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:00:00 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/18 17:17:26 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

int	str_eq(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] == '\0' && b[i] == '\0');
}

int	read_next_token(const char **arg, char *buf, int maxlen)
{
	int	i;

	while (**arg == ' ')
		(*arg)++;
	if (!**arg)
		return (0);
	i = 0;
	while (**arg && **arg != ' ')
	{
		if (i >= maxlen - 1)
			return (-1);
		buf[i++] = *(*arg)++;
	}
	buf[i] = '\0';
	return (1);
}

int	atoi_strict(const char *s, int *out)
{
	int		sign;
	long	res;

	sign = 1;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (!*s)
		return (0);
	res = 0;
	while (*s)
	{
		if (!is_digit(*s))
			return (0);
		res = res * 10 + (*s - '0');
		if (res * sign > INT_MAX || res * sign < INT_MIN)
			return (0);
		s++;
	}
	*out = (int)(res * sign);
	return (1);
}
