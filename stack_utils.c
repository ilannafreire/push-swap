#include "push_swap.h"

void	generic_swap(t_stack **stack)
{
	t_stack	*first;
	t_stack	*second;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	second = first->next;
	first->next = second->next;
	second->next = first;
	*stack = second;
}

void	generic_rotate(t_stack **stack)
{
	t_stack	*first;
	t_stack	*last;

	if (!*stack || !(*stack)->next)
		return ;
	first = *stack;
	*stack = first->next;
	last = *stack;
	while (last->next)
		last = last->next;
	last->next = first;
	first->next = NULL;
}

void	generic_reverse_rotate(t_stack **stack)
{
	t_stack	*second_last;
	t_stack	*last;

	if (!*stack || !(*stack)->next)
		return ;
	second_last = *stack;
	while (second_last->next->next)
		second_last = second_last->next;
	last = second_last->next;
	second_last->next = NULL;
	last->next = *stack;
	*stack = last;
}

void	generic_push(t_stack **dst, t_stack **src)
{
	t_stack	*node;

	if (!*src)
		return ;
	node = *src;
	*src = node->next;
	node->next = *dst;
	*dst = node;
}
