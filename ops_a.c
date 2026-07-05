/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_a.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:02:27 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:32:54 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_sa(t_ctx *data)
{
	swap_top(&data->a);
	data->stats.sa++;
	write_str(1, "sa\n");
}

void	op_pa(t_ctx *data)
{
	transfer_top(&data->a, &data->b);
	data->stats.pa++;
	write_str(1, "pa\n");
}

void	op_ra(t_ctx *data)
{
	shift_fwd(&data->a);
	data->stats.ra++;
	write_str(1, "ra\n");
}

void	op_rra(t_ctx *data)
{
	shift_back(&data->a);
	data->stats.rra++;
	write_str(1, "rra\n");
}
