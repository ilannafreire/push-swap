/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:04:19 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:39:54 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rank_nodes(t_node *a)
{
	t_node	*i;
	t_node	*j;
	int		rank;

	i = a;
	while (i)
	{
		rank = 0;
		j = a;
		while (j)
		{
			if (j->value < i->value)
				rank++;
			j = j->next;
		}
		i->rank = rank;
		i = i->next;
	}
}

static int	log2_ceil(int n)
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

static void	bit_pass(t_ctx *data, int bit)
{
	int	count;
	int	zeros;
	int	i;

	count = list_size(data->a);
	zeros = 0;
	i = 0;
	while (i < count)
	{
		if (!((data->a->rank >> bit) & 1))
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

void	sort_bitwise(t_ctx *data)
{
	int	bits;
	int	bit;

	data->used_algo = ALGO_BITWISE;
	if (!data->a || !data->a->next)
		return ;
	rank_nodes(data->a);
	bits = log2_ceil(list_size(data->a));
	bit = 0;
	while (bit < bits)
	{
		bit_pass(data, bit);
		bit++;
	}
}
