/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:04:34 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:04:36 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	idx_of_min(t_node *a)
{
	int	index;
	int	best_index;
	int	best_value;

	index = 0;
	best_index = 0;
	best_value = a->value;
	while (a)
	{
		if (a->value < best_value)
		{
			best_value = a->value;
			best_index = index;
		}
		a = a->next;
		index++;
	}
	return (best_index);
}

static void	bring_to_front(t_ctx *data, int index)
{
	int	size;

	size = list_size(data->a);
	if (index <= size - index)
	{
		while (index-- > 0)
			op_ra(data);
	}
	else
	{
		index = size - index;
		while (index-- > 0)
			op_rra(data);
	}
}

void	sort_small(t_ctx *data)
{
	data->used_algo = ALGO_TINY;
	while (data->a)
	{
		bring_to_front(data, idx_of_min(data->a));
		op_pb(data);
	}
	while (data->b)
		op_pa(data);
}
