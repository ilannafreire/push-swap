#include "push_swap.h"

void	op_ss(t_data *data)
{
	generic_swap(&data->a);
	generic_swap(&data->b);
	data->bench.ss++;
	put_str(1, "ss\n");
}

void	op_rr(t_data *data)
{
	generic_rotate(&data->a);
	generic_rotate(&data->b);
	data->bench.rr++;
	put_str(1, "rr\n");
}

void	op_rrr(t_data *data)
{
	generic_reverse_rotate(&data->a);
	generic_reverse_rotate(&data->b);
	data->bench.rrr++;
	put_str(1, "rrr\n");
}
