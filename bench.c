/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bench.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:00:00 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/14 23:43:24 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_disorder(t_data *data)
{
	long	scaled;

	scaled = (long)(data->disorder * 10000.0 + 0.5);
	put_str(2, "[bench] disorder: ");
	put_nbr(2, (int)(scaled / 100));
	put_str(2, ".");
	if (scaled % 100 < 10)
		put_str(2, "0");
	put_nbr(2, (int)(scaled % 100));
	put_str(2, "%\n");
}

static void	print_strategy(t_data *data)
{
	put_str(2, "[bench] strategy: ");
	if (data->strategy == STRAT_ADAPTIVE)
		put_str(2, "adaptive\n");
	else if (data->used_strategy == STRAT_SIMPLE)
		put_str(2, "Simple / O(n^2)\n");
	else if (data->used_strategy == STRAT_MEDIUM)
		put_str(2, "Medium / O(n*sqrt(n))\n");
	else
		put_str(2, "Complex / O(n log n)\n");
}

static void	print_rotate_counts(t_data *data)
{
	put_str(2, "\n[bench] ra: ");
	put_nbr(2, data->bench.ra);
	put_str(2, " rb: ");
	put_nbr(2, data->bench.rb);
	put_str(2, " rr: ");
	put_nbr(2, data->bench.rr);
	put_str(2, " rra: ");
	put_nbr(2, data->bench.rra);
	put_str(2, " rrb: ");
	put_nbr(2, data->bench.rrb);
	put_str(2, " rrr: ");
	put_nbr(2, data->bench.rrr);
	put_str(2, "\n");
}

static void	print_counts(t_data *data)
{
	int	total;

	total = data->bench.sa + data->bench.sb + data->bench.ss
		+ data->bench.pa + data->bench.pb + data->bench.ra
		+ data->bench.rb + data->bench.rr + data->bench.rra
		+ data->bench.rrb + data->bench.rrr;
	put_str(2, "[bench] total_ops: ");
	put_nbr(2, total);
	put_str(2, "\n[bench] sa: ");
	put_nbr(2, data->bench.sa);
	put_str(2, " sb: ");
	put_nbr(2, data->bench.sb);
	put_str(2, " ss: ");
	put_nbr(2, data->bench.ss);
	put_str(2, " pa: ");
	put_nbr(2, data->bench.pa);
	put_str(2, " pb: ");
	put_nbr(2, data->bench.pb);
	print_rotate_counts(data);
}

void	print_bench(t_data *data)
{
	print_disorder(data);
	print_strategy(data);
	print_counts(data);
}
