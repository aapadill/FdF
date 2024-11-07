/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_alloc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 11:23:36 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/04 12:17:24 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_ALLOC_H
# define GC_ALLOC_H

#include "libft.h"

typedef struct s_garbage_collector
{
	t_list	*head;
}	t_gc;

#endif
