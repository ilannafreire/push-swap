/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_b.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>           +#+  +:+       +#+   */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:00:00 by ifreire                     #+#    #+#   */
/*   Updated: 2026/07/05 14:00:00 by ifreire              ###   ########.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	op_sb(t_data *data)
{
	generic_swap(&data->b);
	data->bench.sb++;
	put_str(1, "sb\n");
}

void	op_pb(t_data *data)
{
	generic_push(&data->b, &data->a);
	data->bench.pb++;
	put_str(1, "pb\n");
}

void	op_rb(t_data *data)
{
	generic_rotate(&data->b);
	data->bench.rb++;
	put_str(1, "rb\n");
}

void	op_rrb(t_data *data)
{
	generic_reverse_rotate(&data->b);
	data->bench.rrb++;
	put_str(1, "rrb\n");
}
