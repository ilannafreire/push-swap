#include "push_swap.h"

/*
** TODO (O(n^2) strategy): repeatedly find the smallest value still in
** stack a, bring it to the top with the cheaper of ra/rra (compare
** its index to size(a) - index), then pb it onto b. Once every value
** is in b (in descending order), pa everything back onto a.
** Cost: for each of the n values, at most n/2 rotations -> O(n^2).
*/
void	sort_selection(t_data *data)
{
	data->used_strategy = STRAT_SIMPLE;
}
