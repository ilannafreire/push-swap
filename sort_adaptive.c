/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:00:00 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/14 23:43:11 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_data *data)
{
	int	n;

	n = stack_size(data->a);
	if (data->disorder < 0.2 && n <= 100)
		sort_selection(data);
	else if (data->disorder < 0.5)
		sort_chunks(data);
	else
		sort_radix(data);
}
