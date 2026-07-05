/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_chunks_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>           +#+  +:+       +#+   */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:00:00 by ifreire                     #+#    #+#   */
/*   Updated: 2026/07/05 14:00:00 by ifreire              ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	stack_min_max(t_stack *a, int *min_val, int *max_val)
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

int	sqrt_ceil(int n)
{
	int	r;

	r = 0;
	while (r * r < n)
		r++;
	return (r);
}

int	chunk_index(int value, t_chunk_cfg *cfg)
{
	int	idx;

	idx = (value - cfg->min_val) / cfg->width;
	if (idx >= cfg->nb)
		idx = cfg->nb - 1;
	return (idx);
}

void	count_sizes(t_stack *a, int *sizes, t_chunk_cfg *cfg)
{
	while (a)
	{
		sizes[chunk_index(a->value, cfg)]++;
		a = a->next;
	}
}
