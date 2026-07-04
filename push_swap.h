/* push_swap.h - shared types and function prototypes */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_stack
{
	int				value;
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

/* utils.c */
int		my_isdigit(char c);
size_t	my_strlen(const char *s);
void	put_str(int fd, const char *s);
void	put_nbr(int fd, int n);
int		my_atoi_strict(const char *s, int *out);

/* parse.c */
int		parse_args(int argc, char **argv, t_data *data);

/* stack.c */
t_stack	*stack_new(int value);
void	stack_free(t_stack **stack);
int		stack_size(t_stack *stack);
int		stack_is_sorted(t_stack *stack);

/* stack_utils.c */
void	generic_swap(t_stack **stack);
void	generic_rotate(t_stack **stack);
void	generic_reverse_rotate(t_stack **stack);
void	generic_push(t_stack **dst, t_stack **src);

/* ops_a.c */
void	op_sa(t_data *data);
void	op_pa(t_data *data);
void	op_ra(t_data *data);
void	op_rra(t_data *data);

/* ops_b.c */
void	op_sb(t_data *data);
void	op_pb(t_data *data);
void	op_rb(t_data *data);
void	op_rrb(t_data *data);

/* ops_double.c */
void	op_ss(t_data *data);
void	op_rr(t_data *data);
void	op_rrr(t_data *data);

/* disorder.c */
double	compute_disorder(t_stack *a);

/* sort_selection.c (O(n^2)) */
void	sort_selection(t_data *data);

/* sort_chunks_utils.c (cfg = {min_val, width, nb_chunks}) */
void	stack_min_max(t_stack *a, int *min_val, int *max_val);
int		sqrt_ceil(int n);
int		chunk_index(int value, int *cfg);
void	count_sizes(t_stack *a, int *sizes, int *cfg);

/* sort_chunks.c (O(n*sqrt(n))) */
void	sort_chunks(t_data *data);

/* sort_radix.c (O(n log n)) */
void	sort_radix(t_data *data);

/* sort_adaptive.c */
void	sort_adaptive(t_data *data);

/* bench.c */
void	print_bench(t_data *data);

#endif
