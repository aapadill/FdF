/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:19:40 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/05 17:27:16 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include <unistd.h>
# include <stdlib.h>

typedef struct s_node
{
	int				value;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	size_t	size;
}	t_stack;

t_node	*init_node(int value);
t_stack	*init_stack(void);
void	push(t_stack *stack, t_node *new_node);
t_node	*pop(t_stack *stack);
//void	init_push(int value, t_stack *stack);
void	print_stack(t_stack *stack, char *name);
int	free_stack(t_stack *stack, int send_error);

#endif
