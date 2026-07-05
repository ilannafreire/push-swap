/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:01:14 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:32:54 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_entropy(t_ctx *data)
{
	long	scaled;

	scaled = (long)(data->entropy * 10000.0 + 0.5);
	write_str(2, "[stats] entropy: ");
	write_int(2, (int)(scaled / 100));
	write_str(2, ".");
	if (scaled % 100 < 10)
		write_str(2, "0");
	write_int(2, (int)(scaled % 100));
	write_str(2, "%\n");
}

static void	print_algo(t_ctx *data)
{
	write_str(2, "[stats] algo: ");
	if (data->used_algo == ALGO_TINY)
		write_str(2, "Simple / O(n^2)\n");
	else if (data->used_algo == ALGO_GROUPED)
		write_str(2, "Medium / O(n*sqrt(n))\n");
	else
		write_str(2, "Complex / O(n log n)\n");
}

static void	print_ops_extra(t_ctx *data)
{
	write_str(2, "\n[stats] ra: ");
	write_int(2, data->stats.ra);
	write_str(2, " rb: ");
	write_int(2, data->stats.rb);
	write_str(2, " rr: ");
	write_int(2, data->stats.rr);
	write_str(2, " rra: ");
	write_int(2, data->stats.rra);
	write_str(2, " rrb: ");
	write_int(2, data->stats.rrb);
	write_str(2, " rrr: ");
	write_int(2, data->stats.rrr);
	write_str(2, "\n");
}

static void	print_op_counts(t_ctx *data)
{
	int	total;

	total = data->stats.sa + data->stats.sb + data->stats.ss
		+ data->stats.pa + data->stats.pb + data->stats.ra
		+ data->stats.rb + data->stats.rr + data->stats.rra
		+ data->stats.rrb + data->stats.rrr;
	write_str(2, "[stats] total_ops: ");
	write_int(2, total);
	write_str(2, "\n[stats] sa: ");
	write_int(2, data->stats.sa);
	write_str(2, " sb: ");
	write_int(2, data->stats.sb);
	write_str(2, " ss: ");
	write_int(2, data->stats.ss);
	write_str(2, " pa: ");
	write_int(2, data->stats.pa);
	write_str(2, " pb: ");
	write_int(2, data->stats.pb);
	print_ops_extra(data);
}

void	print_stats(t_ctx *data)
{
	print_entropy(data);
	print_algo(data);
	print_op_counts(data);
}
