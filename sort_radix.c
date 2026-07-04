#include "push_swap.h"

/*
** TODO (O(n log n) strategy): classic push_swap radix sort.
** 1. Map values to their rank (0..n-1) so only non-negative numbers
**    matter for the bitwise pass (ranks fit in ceil(log2(n)) bits).
** 2. For each bit from least to most significant: for every element
**    currently in a, if the bit is 0 push it to b (pb), otherwise
**    rotate it (ra) to send it to the back of the pass. After going
**    through all of a, pb the rest, then pb everything from b back
**    to a (pa) in the new order.
** Cost: ceil(log2(n)) passes x O(n) work each -> O(n log n).
*/
void	sort_radix(t_data *data)
{
	data->used_strategy = STRAT_COMPLEX;
}
