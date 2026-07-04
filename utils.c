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
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!my_isdigit(s[i]))
			return (0);
		res = res * 10 + (s[i] - '0');
		if (res * sign > INT_MAX || res * sign < INT_MIN)
			return (0);
		i++;
	}
	*out = (int)(res * sign);
	return (1);
}
