/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_adaptive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:03:47 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:03:49 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_adaptive(t_data *data)
{
	if (data->disorder < 0.2)
		sort_selection(data);
	else if (data->disorder < 0.5)
		sort_chunks(data);
	else
		sort_radix(data);
}
