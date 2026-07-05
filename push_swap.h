/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 02:03:31 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/05 04:29:00 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_node
{
	int				value;
	int				rank;
	struct s_node	*next;
}	t_node;

typedef enum e_algo
{
	ALGO_TINY,
	ALGO_GROUPED,
	ALGO_BITWISE,
	ALGO_AUTO
}	t_algo;

typedef struct s_stats
{
	int	sa;
	int	sb;
	int	ss;
	int	pa;
	int	pb;
	int	ra;
	int	rb;
	int	rr;
	int	rra;
	int	rrb;
	int	rrr;
}	t_stats;

typedef struct s_ctx
{
	t_node		*a;
	t_node		*b;
	t_stats		stats;
	t_algo		algo;
	t_algo		used_algo;
	double		entropy;
	int			stats_mode;
}	t_ctx;

int		is_digit(char c);
size_t	str_len(const char *s);
void	write_str(int fd, const char *s);
void	write_int(int fd, int n);
int		parse_int(const char *s, int *out);

int		parse_args(int argc, char **argv, t_ctx *data);

t_node	*node_new(int value);
void	list_free(t_node **stack);
int		list_size(t_node *stack);
int		list_is_sorted(t_node *stack);

void	swap_top(t_node **stack);
void	shift_fwd(t_node **stack);
void	shift_back(t_node **stack);
void	transfer_top(t_node **dst, t_node **src);

void	op_sa(t_ctx *data);
void	op_pa(t_ctx *data);
void	op_ra(t_ctx *data);
void	op_rra(t_ctx *data);

void	op_sb(t_ctx *data);
void	op_pb(t_ctx *data);
void	op_rb(t_ctx *data);
void	op_rrb(t_ctx *data);

void	op_ss(t_ctx *data);
void	op_rr(t_ctx *data);
void	op_rrr(t_ctx *data);

double	measure_entropy(t_node *a);

void	sort_small(t_ctx *data);

void	find_bounds(t_node *a, int *min_val, int *max_val);
int		int_sqrt(int n);
int		group_of(int value, int *cfg);
void	tally_groups(t_node *a, int *sizes, int *cfg);

void	sort_groups(t_ctx *data);

void	sort_bitwise(t_ctx *data);

void	sort_auto(t_ctx *data);

void	print_stats(t_ctx *data);

#endif
