/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>           +#+  +:+       +#+   */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:00:00 by ifreire                     #+#    #+#   */
/*   Updated: 2026/07/23 12:00:00 by ifreire              ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	str_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	put_str(int fd, const char *s)
{
	write(fd, s, str_len(s));
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
