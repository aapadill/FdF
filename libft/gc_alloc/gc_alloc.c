/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:37:44 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/04 12:20:03 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_alloc.h"

/*
** @description
** Allocates memory of the given size and tracks it using a linked list.
**
** @param
** size: The size of the memory block to allocate.
**
** @return
** A pointer to the allocated memory, or NULL if the allocation fails.
*/
void	*gc_alloc(t_gc *gc, size_t size)
{
	void	*ptr;
	t_list	*node;

	if (!gc || !size)
		return (NULL);
	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	node = ft_lstnew(ptr);
	if (!node)
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_front(&(gc->head), node);
	return (ptr);
}

/*
** @description
** Frees a specific memory block and removes it from the tracking list.
**
** @param
** ptr: The pointer to the memory block to free.
**
** @return
** None
*/
void	gc_free(t_gc *gc, void *ptr)
{
	t_list	*curr;
	t_list	*prev;

	if (!gc | !ptr)
		return ;
	curr = gc->head;
	prev = NULL;
	while (curr)
	{
		if (curr->content == ptr)
		{
			if (prev)
				prev->next = curr->next;
			else
				gc->head = curr->next;
			free(curr->content);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

/*
** @description
** Frees all allocated memory blocks and clears the tracking list.
**
** @param
** None
**
** @return
** None
*/
void	gc_free_all(t_gc *gc)
{
	t_list	*curr;
	t_list	*temp;

	if (!gc)
		return ;
	curr = gc->head;
	while (curr)
	{
		temp = curr->next;
		free(curr->content);
		free(curr);
		curr = temp;
	}
	gc->head = NULL;
}
