/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_auto.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:03:47 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 02:03:49 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_auto(t_ctx *data)
{
	if (data->entropy < 0.2)
		sort_small(data);
	else if (data->entropy < 0.5)
		sort_groups(data);
	else
		sort_bitwise(data);
}
