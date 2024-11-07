/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:26:20 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/05 12:20:57 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

/*
** @description
** Pop the top node of the stack
** Do nothing if there is no node
**
** @param
** Pointer to stack
**
** @return
** Pointer to popped node or
** NULL if stack is empty
*/
t_node	*pop(t_stack *stack)
{
	t_node	*popped;

	if (!stack->top || !stack->size)
		return (NULL);
	popped = stack->top;
	stack->top = popped->next;
	stack->size -= 1;
	popped->next = NULL;
	return (popped);
}

/*
** @description
** Push one node to the top of the stack
**
** @param
** Pointer to node
** Pointer to stack
**
** @return
*/
void	push(t_stack *stack, t_node *node)
{
	if (!stack->top)
	{
		stack->top = node;
		stack->size++;
		return ;
	}
	node->next = stack->top;
	stack->top = node;
	stack->size++;
}

