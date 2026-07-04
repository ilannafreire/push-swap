#include "push_swap.h"

static int	str_eq(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] == '\0' && b[i] == '\0');
}

static int	is_flag(const char *arg, t_data *data)
{
	if (str_eq(arg, "--simple"))
		data->strategy = STRAT_SIMPLE;
	else if (str_eq(arg, "--medium"))
		data->strategy = STRAT_MEDIUM;
	else if (str_eq(arg, "--complex"))
		data->strategy = STRAT_COMPLEX;
	else if (str_eq(arg, "--adaptive"))
		data->strategy = STRAT_ADAPTIVE;
	else if (str_eq(arg, "--bench"))
		data->bench_mode = 1;
	else
		return (0);
	return (1);
}

static int	add_number(t_data *data, int value)
{
	t_stack	*node;
	t_stack	*cur;

	cur = data->a;
	while (cur)
	{
		if (cur->value == value)
			return (0);
		cur = cur->next;
	}
	node = stack_new(value);
	if (!data->a)
		data->a = node;
	else
	{
		cur = data->a;
		while (cur->next)
			cur = cur->next;
		cur->next = node;
	}
	return (1);
}

static int	build_stack(t_data *data, int argc, char **argv, int start)
{
	int	i;
	int	value;

	i = start;
	while (i < argc)
	{
		if (!is_flag(argv[i], data))
		{
			if (!my_atoi_strict(argv[i], &value))
				return (0);
			if (!add_number(data, value))
				return (0);
		}
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_data *data)
{
	data->a = NULL;
	data->b = NULL;
	data->strategy = STRAT_ADAPTIVE;
	data->used_strategy = STRAT_SIMPLE;
	data->bench_mode = 0;
	data->disorder = 0.0;
	data->bench.sa = 0;
	data->bench.sb = 0;
	data->bench.ss = 0;
	data->bench.pa = 0;
	data->bench.pb = 0;
	data->bench.ra = 0;
	data->bench.rb = 0;
	data->bench.rr = 0;
	data->bench.rra = 0;
	data->bench.rrb = 0;
	data->bench.rrr = 0;
	if (!build_stack(data, argc, argv, 1))
		return (0);
	return (1);
}
