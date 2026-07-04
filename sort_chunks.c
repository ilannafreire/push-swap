#include "push_swap.h"

/*
** TODO (O(n*sqrt(n)) strategy): split the value range into ~sqrt(n)
** chunks. For each chunk (from lowest to highest), scan stack a and
** push every value belonging to that chunk onto b, rotating a as
** needed to bring candidates to the top. Finally pa everything back.
** Cost: sqrt(n) chunks x O(n) scan each -> O(n*sqrt(n)).
*/
void	sort_chunks(t_data *data)
{
	data->used_strategy = STRAT_MEDIUM;
}
