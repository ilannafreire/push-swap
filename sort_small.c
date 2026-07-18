/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:00:00 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/18 17:17:26 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	sort_2(t_data *data)
{
	if (data->a->value > data->a->next->value)
		op_sa(data);
}

static void	sort_3(t_data *data)
{
	int	v0;
	int	v1;
	int	v2;

	v0 = data->a->value;
	v1 = data->a->next->value;
	v2 = data->a->next->next->value;
	if (v1 < v0 && v0 < v2)
		op_sa(data);
	else if (v2 < v0 && v0 < v1)
		op_rra(data);
	else if (v1 < v2 && v2 < v0)
		op_ra(data);
	else if (v0 < v2 && v2 < v1)
	{
		op_sa(data);
		op_ra(data);
	}
	else if (v2 < v1 && v1 < v0)
	{
		op_sa(data);
		op_rra(data);
	}
}

static int	find_min_pos(t_stack *head)
{
	t_stack	*cur;
	int		min_val;
	int		idx;
	int		min_idx;

	cur = head;
	min_val = cur->value;
	idx = 0;
	min_idx = 0;
	while (cur)
	{
		if (cur->value < min_val)
		{
			min_val = cur->value;
			min_idx = idx;
		}
		cur = cur->next;
		idx++;
	}
	return (min_idx);
}

static void	push_min_to_b(t_data *data)
{
	int		sz;
	int		min_idx;

	min_idx = find_min_pos(data->a);
	sz = stack_size(data->a);
	if (min_idx <= sz - min_idx)
		while (min_idx-- > 0)
			op_ra(data);
	else
	{
		min_idx = sz - min_idx;
		while (min_idx-- > 0)
			op_rra(data);
	}
	op_pb(data);
}

void	sort_small(t_data *data)
{
	int	n;

	n = stack_size(data->a);
	if (n <= 1)
		return ;
	if (n == 2)
		sort_2(data);
	else if (n == 3)
		sort_3(data);
	else
	{
		push_min_to_b(data);
		if (n == 5)
			push_min_to_b(data);
		sort_3(data);
		op_pa(data);
		if (n == 5)
			op_pa(data);
	}
}
