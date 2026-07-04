#include "push_swap.h"

/*
** Dispatch based on the disorder metric measured in main() before any
** operation was executed (subject VI.3.3, thresholds below).
*/
void	sort_adaptive(t_data *data)
{
	if (data->disorder < 0.2)
		sort_selection(data);
	else if (data->disorder < 0.5)
		sort_chunks(data);
	else
		sort_radix(data);
}
