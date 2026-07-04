#include "push_swap.h"

void	op_sa(t_data *data)
{
	generic_swap(&data->a);
	data->bench.sa++;
	put_str(1, "sa\n");
}

void	op_pa(t_data *data)
{
	generic_push(&data->a, &data->b);
	data->bench.pa++;
	put_str(1, "pa\n");
}

void	op_ra(t_data *data)
{
	generic_rotate(&data->a);
	data->bench.ra++;
	put_str(1, "ra\n");
}

void	op_rra(t_data *data)
{
	generic_reverse_rotate(&data->a);
	data->bench.rra++;
	put_str(1, "rra\n");
}
