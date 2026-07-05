/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_groups.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:04:08 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:32:54 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	scatter_chunks(t_ctx *data, int *cfg)
{
	int	chunk_id;
	int	remaining;
	int	i;

	chunk_id = 0;
	while (chunk_id < cfg[2])
	{
		remaining = list_size(data->a);
		i = 0;
		while (i < remaining)
		{
			if (group_of(data->a->value, cfg) == chunk_id)
				op_pb(data);
			else
				op_ra(data);
			i++;
		}
		chunk_id++;
	}
}

static int	best_in_window(t_node *a, int low, int high)
{
	t_node	*cur;
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

static void	collect_chunk(t_ctx *data, int low, int high, int size)
{
	int	best_pos;
	int	sz;

	while (size-- > 0)
	{
		best_pos = best_in_window(data->a, low, high);
		sz = list_size(data->a);
		if (best_pos <= sz - best_pos)
			while (best_pos-- > 0)
				op_ra(data);
		else
		{
			sz = sz - best_pos;
			while (sz-- > 0)
				op_rra(data);
		}
		op_pb(data);
	}
}

static void	reassemble(t_ctx *data, int *sizes, int *cfg)
{
	int	chunk_id;
	int	low;
	int	i;

	chunk_id = cfg[2] - 1;
	while (chunk_id >= 0)
	{
		i = sizes[chunk_id];
		while (i-- > 0)
			op_pa(data);
		low = cfg[0] + chunk_id * cfg[1];
		collect_chunk(data, low, low + cfg[1] - 1, sizes[chunk_id]);
		i = sizes[chunk_id];
		while (i-- > 0)
			op_pa(data);
		chunk_id--;
	}
}

void	sort_groups(t_ctx *data)
{
	int	min_val;
	int	max_val;
	int	cfg[3];
	int	*sizes;

	data->used_algo = ALGO_GROUPED;
	if (!data->a || !data->a->next)
		return ;
	find_bounds(data->a, &min_val, &max_val);
	cfg[2] = int_sqrt(list_size(data->a));
	cfg[0] = min_val;
	cfg[1] = (max_val - min_val) / cfg[2] + 1;
	sizes = (int *)calloc(cfg[2], sizeof(int));
	if (!sizes)
	{
		write_str(2, "Error\n");
		return ;
	}
	tally_groups(data->a, sizes, cfg);
	scatter_chunks(data, cfg);
	reassemble(data, sizes, cfg);
	free(sizes);
}
