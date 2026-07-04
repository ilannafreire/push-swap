#include "push_swap.h"

/*
** One sweep of the whole current a per chunk: whatever belongs to
** chunk_id is pushed to b (pb), everything else is rotated (ra) to
** be looked at again later. Processed from the lowest chunk up to
** the highest, so chunk (nb-1) (largest values) ends up on top of b
** -- reassemble() below then pulls chunks back in the opposite
** order, so the smallest chunk ends up on top of a at the very end.
*/
static void	distribute(t_data *data, int *cfg)
{
	int	chunk_id;
	int	remaining;
	int	i;

	chunk_id = 0;
	while (chunk_id < cfg[2])
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

/*
** a currently holds this chunk's "size" raw values on top (already
** finished, smaller chunks sit below, untouched). Extract them one
** at a time in ascending order onto b, then pa them all back so they
** land, correctly sorted, above the previously finished chunks.
*/
static void	local_sort_chunk(t_data *data, int low, int high, int size)
{
	t_stack	*cur;
	int		best_pos;
	int		best_val;
	int		pos;

	while (size-- > 0)
	{
		cur = data->a;
		best_pos = -1;
		best_val = 0;
		pos = 0;
		while (cur)
		{
			if (cur->value >= low && cur->value <= high)
				if (best_pos == -1 || cur->value < best_val)
				{
					best_val = cur->value;
					best_pos = pos;
				}
			cur = cur->next;
			pos++;
		}
		if (best_pos <= stack_size(data->a) - best_pos)
			while (best_pos-- > 0)
				op_ra(data);
		else
		{
			pos = stack_size(data->a) - best_pos;
			while (pos-- > 0)
				op_rra(data);
		}
		op_pb(data);
	}
}

/*
** Pull chunks back from b in HIGHEST-to-LOWEST order: the highest
** chunk is pulled first (a is empty, so it becomes the bottom of the
** rebuilt stack), then each next-lower chunk is pulled on top of it.
** Chunk 0 (smallest) is pulled last, so it ends up on top of a.
*/
static void	reassemble(t_data *data, int *sizes, int *cfg)
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
		local_sort_chunk(data, low, low + cfg[1] - 1, sizes[chunk_id]);
		i = sizes[chunk_id];
		while (i-- > 0)
			op_pa(data);
		chunk_id--;
	}
}

/*
** Splits the value range into ceil(sqrt(n)) chunks, distributes the
** stack into those chunks (one O(current size) sweep per chunk), then
** rebuilds a chunk by chunk (highest first, so the smallest chunk
** ends up on top last), fixing each chunk's internal order right
** after it is pulled back from b.
** Distribution: sqrt(n) sweeps x O(n) each -> O(n*sqrt(n)).
** Local fix: sqrt(n) chunks x O(sqrt(n)^2) each -> O(n*sqrt(n)).
*/
void	sort_chunks(t_data *data)
{
	int	min_val;
	int	max_val;
	int	cfg[3];
	int	*sizes;
	int	i;

	data->used_strategy = STRAT_MEDIUM;
	if (!data->a || !data->a->next)
		return ;
	stack_min_max(data->a, &min_val, &max_val);
	cfg[2] = sqrt_ceil(stack_size(data->a));
	cfg[0] = min_val;
	cfg[1] = (max_val - min_val) / cfg[2] + 1;
	sizes = malloc(sizeof(int) * cfg[2]);
	if (!sizes)
	{
		put_str(2, "Error\n");
		exit(1);
	}
	i = -1;
	while (++i < cfg[2])
		sizes[i] = 0;
	count_sizes(data->a, sizes, cfg);
	distribute(data, cfg);
	reassemble(data, sizes, cfg);
	free(sizes);
}
