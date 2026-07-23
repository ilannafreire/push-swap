/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 14:00:00 by ifreire           #+#    #+#             */
/*   Updated: 2026/07/18 17:17:26 by ifreire          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_stack
{
	int				value;
	int				rank;
	struct s_stack	*next;
}	t_stack;

typedef enum e_strategy
{
	STRAT_SIMPLE,
	STRAT_MEDIUM,
	STRAT_COMPLEX,
	STRAT_ADAPTIVE
}	t_strategy;

typedef struct s_bench
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
}	t_bench;

typedef struct s_data
{
	t_stack		*a;
	t_stack		*b;
	t_bench		bench;
	t_strategy	strategy;
	t_strategy	used_strategy;
	double		disorder;
	int			bench_mode;
}	t_data;

int		is_digit(char c);
int		atoi_strict(const char *s, int *out);
int		str_eq(const char *a, const char *b);
int		read_next_token(const char **arg, char *buf, int maxlen);

size_t	str_len(const char *s);
void	put_str(int fd, const char *s);
void	put_nbr(int fd, int n);

int		parse_args(int argc, char **argv, t_data *data);

t_stack	*stack_new(int value);
void	stack_free(t_stack **stack);
int		stack_size(t_stack *stack);
int		stack_is_sorted(t_stack *stack);

void	generic_swap(t_stack **stack);
void	generic_rotate(t_stack **stack);
void	generic_reverse_rotate(t_stack **stack);
void	generic_push(t_stack **dst, t_stack **src);

void	op_sa(t_data *data);
void	op_pa(t_data *data);
void	op_ra(t_data *data);
void	op_rra(t_data *data);

void	op_sb(t_data *data);
void	op_pb(t_data *data);
void	op_rb(t_data *data);
void	op_rrb(t_data *data);

void	op_ss(t_data *data);
void	op_rr(t_data *data);
void	op_rrr(t_data *data);

double	compute_disorder(t_stack *a);

void	sort_selection(t_data *data);
void	sort_small(t_data *data);

void	assign_ranks(t_stack *a);
int		sqrt_ceil(int n);
int		find_max_rank_b(t_stack *b, int lo, int hi);
void	bring_b_top(t_data *data, int pos);

void	sort_chunks(t_data *data);

void	sort_radix(t_data *data);

void	sort_adaptive(t_data *data);

void	print_bench(t_data *data);

#endif
