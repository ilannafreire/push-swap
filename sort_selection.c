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

/*
** Classic selection sort: repeatedly extract the smallest remaining
** value from a and push it onto b. Because we always extract the
** current minimum, b ends up sorted in descending order (top to
** bottom); pushing everything back with pa then restores ascending
** order in a (two reversals cancel out).
** Cost: n extractions x up to n/2 rotations each -> O(n^2).
*/
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
