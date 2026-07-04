#include "push_swap.h"

/*
** cfg holds the three numbers every chunk helper needs:
** cfg[0] = min value in a, cfg[1] = chunk width, cfg[2] = nb of chunks.
** Bundling them keeps every function at 2-3 parameters (norm limit 4).
*/

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

int	chunk_index(int value, int *cfg)
{
	int	idx;

	idx = (value - cfg[0]) / cfg[1];
	if (idx >= cfg[2])
		idx = cfg[2] - 1;
	return (idx);
}

void	count_sizes(t_stack *a, int *sizes, int *cfg)
{
	while (a)
	{
		sizes[chunk_index(a->value, cfg)]++;
		a = a->next;
	}
}
