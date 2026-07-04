#include "push_swap.h"

static void	run_strategy(t_data *data)
{
	if (data->strategy == STRAT_SIMPLE)
		sort_selection(data);
	else if (data->strategy == STRAT_MEDIUM)
		sort_chunks(data);
	else if (data->strategy == STRAT_COMPLEX)
		sort_radix(data);
	else
		sort_adaptive(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2)
		return (0);
	if (!parse_args(argc, argv, &data))
	{
		put_str(2, "Error\n");
		return (1);
	}
	data.disorder = compute_disorder(data.a);
	if (!stack_is_sorted(data.a))
		run_strategy(&data);
	if (data.bench_mode)
		print_bench(&data);
	stack_free(&data.a);
	stack_free(&data.b);
	return (0);
}
