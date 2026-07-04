#include "push_swap.h"

/*
** Rank of value = how many elements (across a and b combined, which
** always adds up to every original element, however split) are
** smaller than it. Values are unique, so rank is a bijection to
** 0..n-1 and preserves order: sorting by rank == sorting by value.
*/
static int	get_rank(t_data *data, int value)
{
	t_stack	*cur;
	int		rank;

	rank = 0;
	cur = data->a;
	while (cur)
	{
		if (cur->value < value)
			rank++;
		cur = cur->next;
	}
	cur = data->b;
	while (cur)
	{
		if (cur->value < value)
			rank++;
		cur = cur->next;
	}
	return (rank);
}

static int	bits_needed(int n)
{
	int	bits;
	int	limit;

	bits = 0;
	limit = 1;
	while (limit < n)
	{
		limit = limit * 2;
		bits++;
	}
	return (bits);
}

/*
** Stable binary partition on one bit: elements with this bit at 0 go
** to b (pb), elements with it at 1 stay in a (ra defers them to the
** back, preserving their relative order). Restoring the 0-bucket on
** top of a (pa) keeps both buckets internally ordered as before this
** pass -- the classic LSD radix invariant.
*/
static void	radix_pass(t_data *data, int bit)
{
	int	count;
	int	zeros;
	int	i;

	count = stack_size(data->a);
	zeros = 0;
	i = 0;
	while (i < count)
	{
		if (!((get_rank(data, data->a->value) >> bit) & 1))
		{
			op_pb(data);
			zeros++;
		}
		else
			op_ra(data);
		i++;
	}
	i = 0;
	while (i < zeros)
	{
		op_pa(data);
		i++;
	}
}

/*
** Radix sort on rank bits (0 = smallest .. n-1 = largest), LSB first.
** ceil(log2(n)) passes, each O(n) operations -> O(n log n).
*/
void	sort_radix(t_data *data)
{
	int	bits;
	int	bit;

	data->used_strategy = STRAT_COMPLEX;
	if (!data->a || !data->a->next)
		return ;
	bits = bits_needed(stack_size(data->a));
	bit = 0;
	while (bit < bits)
	{
		radix_pass(data, bit);
		bit++;
	}
}
