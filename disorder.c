#include "push_swap.h"

/*
** disorder = mistakes / total_pairs, measured on stack a before any
** operation is executed. A mistake is a pair (i, j) with i before j
** in the stack where value[i] > value[j]. See subject VI.3.2.
*/
double	compute_disorder(t_stack *a)
{
	t_stack	*i;
	t_stack	*j;
	long	mistakes;
	long	total_pairs;

	mistakes = 0;
	total_pairs = 0;
	i = a;
	while (i)
	{
		j = i->next;
		while (j)
		{
			total_pairs++;
			if (i->value > j->value)
				mistakes++;
			j = j->next;
		}
		i = i->next;
	}
	if (total_pairs == 0)
		return (0.0);
	return ((double)mistakes / (double)total_pairs);
}
