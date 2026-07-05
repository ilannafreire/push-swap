/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_selection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>           +#+  +:+       +#+   */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:00:00 by ifreire                     #+#    #+#   */
/*   Updated: 2026/07/05 14:00:00 by ifreire              ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_min_index(t_stack *a)
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

static void	rotate_to_top(t_data *data, int index)
{
	int	size;

	size = stack_size(data->a);
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

void	sort_selection(t_data *data)
{
	data->used_strategy = STRAT_SIMPLE;
	while (data->a)
	{
		rotate_to_top(data, find_min_index(data->a));
		op_pb(data);
	}
	while (data->b)
		op_pa(data);
}
