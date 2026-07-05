/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_chunks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>           +#+  +:+       +#+   */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:00:00 by ifreire                     #+#    #+#   */
/*   Updated: 2026/07/05 14:00:00 by ifreire              ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	distribute_low_to_high(t_data *data, t_chunk_cfg *cfg)
{
	int	chunk_id;
	int	remaining;
	int	i;

	chunk_id = 0;
	while (chunk_id < cfg->nb)
	{
		remaining = stack_size(data->a);
		i = 0;
		while (i < remaining)
		{
			if (chunk_index(data->a->value, cfg) == chunk_id)
				op_pb(data);
			else
				op_ra(data);
			i++;
		}
		chunk_id++;
	}
}

static int	find_in_range(t_stack *a, int low, int high)
{
	t_stack	*cur;
	int		best_pos;
	int		best_val;
	int		pos;

	cur = a;
	best_pos = -1;
	best_val = 0;
	pos = 0;
	while (cur)
	{
		if (cur->value >= low && cur->value <= high)
		{
			if (best_pos == -1 || cur->value < best_val)
			{
				best_val = cur->value;
				best_pos = pos;
			}
		}
		cur = cur->next;
		pos++;
	}
	return (best_pos);
}

static void	local_sort_chunk(t_data *data, int low, int high, int size)
{
	int	best_pos;
	int	size_a;
	int	dist;

	while (size-- > 0)
	{
		best_pos = find_in_range(data->a, low, high);
		size_a = stack_size(data->a);
		if (best_pos <= size_a - best_pos)
			while (best_pos-- > 0)
				op_ra(data);
		else
		{
			dist = size_a - best_pos;
			while (dist-- > 0)
				op_rra(data);
		}
		op_pb(data);
	}
}

static void	reassemble_high_to_low(t_data *data, int *sizes, t_chunk_cfg *cfg)
{
	int	chunk_id;
	int	low;
	int	i;

	chunk_id = cfg->nb - 1;
	while (chunk_id >= 0)
	{
		i = sizes[chunk_id];
		while (i-- > 0)
			op_pa(data);
		low = cfg->min_val + chunk_id * cfg->width;
		local_sort_chunk(data, low, low + cfg->width - 1, sizes[chunk_id]);
		i = sizes[chunk_id];
		while (i-- > 0)
			op_pa(data);
		chunk_id--;
	}
}

void	sort_chunks(t_data *data)
{
	int			min_val;
	int			max_val;
	t_chunk_cfg	cfg;
	int			*sizes;

	data->used_strategy = STRAT_MEDIUM;
	if (!data->a || !data->a->next)
		return ;
	stack_min_max(data->a, &min_val, &max_val);
	cfg.nb = sqrt_ceil(stack_size(data->a));
	cfg.min_val = min_val;
	cfg.width = (max_val - min_val) / cfg.nb + 1;
	sizes = (int *)calloc(cfg.nb, sizeof(int));
	if (!sizes)
	{
		put_str(2, "Error\n");
		return ;
	}
	count_sizes(data->a, sizes, &cfg);
	distribute_low_to_high(data, &cfg);
	reassemble_high_to_low(data, sizes, &cfg);
	free(sizes);
}
