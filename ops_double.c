/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_double.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:02:55 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:02:57 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_ss(t_ctx *data)
{
	swap_top(&data->a);
	swap_top(&data->b);
	data->stats.ss++;
	write_str(1, "ss\n");
}

void	op_rr(t_ctx *data)
{
	shift_fwd(&data->a);
	shift_fwd(&data->b);
	data->stats.rr++;
	write_str(1, "rr\n");
}

void	op_rrr(t_ctx *data)
{
	shift_back(&data->a);
	shift_back(&data->b);
	data->stats.rrr++;
	write_str(1, "rrr\n");
}
