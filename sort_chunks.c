/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_chunks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:00:00 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/14 23:43:11 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	distribute(t_data *data, int nb, int chunk_size)
{
	int	chunk_id;
	int	remaining;
	int	i;
	int	ck;

	chunk_id = 0;
	while (chunk_id < nb)
	{
		remaining = stack_size(data->a);
		i = 0;
		while (i < remaining)
		{
			ck = data->a->rank / chunk_size;
			if (ck >= nb)
				ck = nb - 1;
			if (ck == chunk_id)
				op_pb(data);
			else
				op_ra(data);
			i++;
		}
		chunk_id++;
	}
}

static void	reassemble(t_data *data, int nb, int chunk_size, int n)
{
	int	chunk_id;
	int	lo;
	int	hi;
	int	cnt;
	int	pos;

	chunk_id = nb - 1;
	while (chunk_id >= 0)
	{
		lo = chunk_id * chunk_size;
		hi = (chunk_id < nb - 1) ? lo + chunk_size - 1 : n - 1;
		cnt = hi - lo + 1;
		while (cnt-- > 0)
		{
			pos = find_max_rank_b(data->b, lo, hi);
			bring_b_top(data, pos);
			op_pa(data);
		}
		chunk_id--;
	}
}

void	sort_chunks(t_data *data)
{
	int	n;
	int	nb;
	int	chunk_size;

	data->used_strategy = STRAT_MEDIUM;
	if (!data->a || !data->a->next)
		return ;
	n = stack_size(data->a);
	assign_ranks(data->a);
	nb = sqrt_ceil(n);
	chunk_size = n / nb;
	if (chunk_size == 0)
		chunk_size = 1;
	distribute(data, nb, chunk_size);
	reassemble(data, nb, chunk_size, n);
}
