/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:03:17 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:03:22 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	same_str(const char *a, const char *b)
{
	int	i;

	i = 0;
	while (a[i] && b[i] && a[i] == b[i])
		i++;
	return (a[i] == '\0' && b[i] == '\0');
}

static int	is_opt(const char *arg, t_ctx *data)
{
	if (same_str(arg, "--simple"))
		data->algo = ALGO_TINY;
	else if (same_str(arg, "--medium"))
		data->algo = ALGO_GROUPED;
	else if (same_str(arg, "--complex"))
		data->algo = ALGO_BITWISE;
	else if (same_str(arg, "--adaptive"))
		data->algo = ALGO_AUTO;
	else if (same_str(arg, "--stats"))
		data->stats_mode = 1;
	else
		return (0);
	return (1);
}

static int	append_val(t_ctx *data, int value)
{
	t_node	*node;
	t_node	*cur;

	cur = data->a;
	while (cur)
	{
		if (cur->value == value)
			return (0);
		cur = cur->next;
	}
	node = node_new(value);
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

static int	init_list(t_ctx *data, int argc, char **argv, int start)
{
	int	i;
	int	value;

	i = start;
	while (i < argc)
	{
		if (!is_opt(argv[i], data))
		{
			if (!parse_int(argv[i], &value))
				return (0);
			if (!append_val(data, value))
				return (0);
		}
		i++;
	}
	return (1);
}

int	parse_args(int argc, char **argv, t_ctx *data)
{
	data->a = NULL;
	data->b = NULL;
	data->algo = ALGO_AUTO;
	data->used_algo = ALGO_TINY;
	data->stats_mode = 0;
	data->entropy = 0.0;
	data->stats.sa = 0;
	data->stats.sb = 0;
	data->stats.ss = 0;
	data->stats.pa = 0;
	data->stats.pb = 0;
	data->stats.ra = 0;
	data->stats.rb = 0;
	data->stats.rr = 0;
	data->stats.rra = 0;
	data->stats.rrb = 0;
	data->stats.rrr = 0;
	if (!init_list(data, argc, argv, 1))
		return (0);
	return (1);
}
