/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 04:26:58 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 04:27:22 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

size_t	str_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	write_str(int fd, const char *s)
{
	write(fd, s, str_len(s));
}

void	write_int(int fd, int n)
{
	long	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		write_str(fd, "-");
		nb = -nb;
	}
	if (nb >= 10)
		write_int(fd, (int)(nb / 10));
	c = (char)(nb % 10) + '0';
	write(fd, &c, 1);
}

int	parse_int(const char *s, int *out)
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
