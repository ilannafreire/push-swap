/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_chunks_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:00:00 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/14 23:43:11 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	assign_ranks(t_stack *a)
{
	t_stack	*i;
	t_stack	*j;
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

int	sqrt_ceil(int n)
{
	int	r;

	r = 0;
	while (r * r < n)
		r++;
	return (r);
}

int	find_max_rank_b(t_stack *b, int lo, int hi)
{
	t_stack	*cur;
	int		best_pos;
	int		best_rank;
	int		pos;

	cur = b;
	best_pos = -1;
	best_rank = -1;
	pos = 0;
	while (cur)
	{
		if (cur->rank >= lo && cur->rank <= hi && cur->rank > best_rank)
		{
			best_rank = cur->rank;
			best_pos = pos;
		}
		cur = cur->next;
		pos++;
	}
	return (best_pos);
}

void	bring_b_top(t_data *data, int pos)
{
	int	size;
	int	dist;

	size = stack_size(data->b);
	if (pos <= size - pos)
	{
		while (pos-- > 0)
			op_rb(data);
	}
	else
	{
		dist = size - pos;
		while (dist-- > 0)
			op_rrb(data);
	}
}
