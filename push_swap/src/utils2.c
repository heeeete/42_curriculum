/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 16:52:58 by huipark           #+#    #+#             */
/*   Updated: 2022/11/20 16:53:22 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	aligned_already(t_list *head)
{
	while (head->next)
	{
		if (head->value > head->next->value)
			head = head->next;
		else
			return ;
	}
	exit(0);
}

void	zero(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}
