/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:02:38 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:02:44 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_sb(t_ctx *data)
{
	swap_top(&data->b);
	data->stats.sb++;
	write_str(1, "sb\n");
}

void	op_pb(t_ctx *data)
{
	transfer_top(&data->b, &data->a);
	data->stats.pb++;
	write_str(1, "pb\n");
}

void	op_rb(t_ctx *data)
{
	shift_fwd(&data->b);
	data->stats.rb++;
	write_str(1, "rb\n");
}

void	op_rrb(t_ctx *data)
{
	shift_back(&data->b);
	data->stats.rrb++;
	write_str(1, "rrb\n");
}
