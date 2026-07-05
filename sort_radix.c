/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_radix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:04:19 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:04:23 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_rank(t_data *data, int value)
{
	t_stack	*cur;
	int		rank;

	rank = 0;
	cur = data->a;
	while (cur)
	{
		if (cur->value < value)
			rank++;
		cur = cur->next;
	}
	cur = data->b;
	while (cur)
	{
		if (cur->value < value)
			rank++;
		cur = cur->next;
	}
	return (rank);
}

static int	bits_needed(int n)
{
	int	bits;
	int	limit;

	bits = 0;
	limit = 1;
	while (limit < n)
	{
		limit = limit * 2;
		bits++;
	}
	return (bits);
}

static void	radix_pass(t_data *data, int bit)
{
	int	count;
	int	zeros;
	int	i;

	count = stack_size(data->a);
	zeros = 0;
	i = 0;
	while (i < count)
	{
		if (!((get_rank(data, data->a->value) >> bit) & 1))
		{
			op_pb(data);
			zeros++;
		}
		else
			op_ra(data);
		i++;
	}
	i = 0;
	while (i < zeros)
	{
		op_pa(data);
		i++;
	}
}

void	sort_radix(t_data *data)
{
	int	bits;
	int	bit;

	data->used_strategy = STRAT_COMPLEX;
	if (!data->a || !data->a->next)
		return ;
	bits = bits_needed(stack_size(data->a));
	bit = 0;
	while (bit < bits)
	{
		radix_pass(data, bit);
		bit++;
	}
}
