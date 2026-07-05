/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:01:57 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:02:03 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	run_algo(t_ctx *data)
{
	if (data->algo == ALGO_TINY)
		sort_small(data);
	else if (data->algo == ALGO_GROUPED)
		sort_groups(data);
	else if (data->algo == ALGO_BITWISE)
		sort_bitwise(data);
	else
		sort_auto(data);
}

int	main(int argc, char **argv)
{
	t_ctx	data;

	if (argc < 2)
		return (0);
	if (!parse_args(argc, argv, &data))
	{
		write_str(2, "Error\n");
		return (1);
	}
	data.entropy = measure_entropy(data.a);
	if (!list_is_sorted(data.a))
		run_algo(&data);
	if (data.stats_mode)
		print_stats(&data);
	list_free(&data.a);
	list_free(&data.b);
	return (0);
}
