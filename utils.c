/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:05:17 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:32:54 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	my_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

size_t	my_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	put_str(int fd, const char *s)
{
	write(fd, s, my_strlen(s));
}

void	put_nbr(int fd, int n)
{
	long	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		put_str(fd, "-");
		nb = -nb;
	}
	if (nb >= 10)
		put_nbr(fd, (int)(nb / 10));
	c = (char)(nb % 10) + '0';
	write(fd, &c, 1);
}

int	my_atoi_strict(const char *s, int *out)
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
		if (!my_isdigit(*s))
			return (0);
		res = res * 10 + (*s - '0');
		if (res * sign > INT_MAX || res * sign < INT_MIN)
			return (0);
		s++;
	}
	*out = (int)(res * sign);
	return (1);
}
