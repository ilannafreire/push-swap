/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_io_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:03:58 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:04:00 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	find_bounds(t_node *a, int *min_val, int *max_val)
{
	*min_val = a->value;
	*max_val = a->value;
	while (a)
	{
		if (a->value < *min_val)
			*min_val = a->value;
		if (a->value > *max_val)
			*max_val = a->value;
		a = a->next;
	}
}

int	int_sqrt(int n)
{
	int	r;

	r = 0;
	while (r * r < n)
		r++;
	return (r);
}

int	group_of(int value, int *cfg)
{
	int	idx;

	idx = (value - cfg[0]) / cfg[1];
	if (idx >= cfg[2])
		idx = cfg[2] - 1;
	return (idx);
}

void	tally_groups(t_node *a, int *sizes, int *cfg)
{
	while (a)
	{
		sizes[group_of(a->value, cfg)]++;
		a = a->next;
	}
}
