#include "push_swap.h"

void	sort_adaptive(t_data *data)
{
	if (data->disorder < 0.2)
		sort_selection(data);
	else if (data->disorder < 0.5)
		sort_chunks(data);
	else
		sort_radix(data);
}
