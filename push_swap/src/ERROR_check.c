/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ERROR_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huipark <huipark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:47:35 by huipark           #+#    #+#             */
/*   Updated: 2022/11/24 03:56:59 by huipark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/push_swap.h"

void	error_check(int argc, char *argv[])
{
	int		i;
	int		j;
	char	**str;

	while (argc-- > 1)
	{
		i = 0;
		str = ft_split(argv[argc], ' ');
		while (str[i])
		{
			j = 0;
			while (str[i][j])
			{
				j += ((str[i][0] == '-' || str[i][0] == '+') && j == 0);
				if (str[i][j] < '0' || str[i][j] > '9')
					error();
				j++;
			}
			if (ft_atoi(str[i]) > INT_MAX || ft_atoi(str[i]) < INT_MIN)
				error();
			i++;
		}
		if (!str[0])
			error();
		ft_free(str);
	}
}

void	error_check2(int argc, char *argv[], t_list *head)
{
	t_list	*temp;

	if (argc == 1)
		exit(0);
	while (head->next != NULL && argc != 2)
	{
		head = head->next;
		if (head->next != NULL)
			temp = head->next;
		while (temp != NULL)
		{
			if (head->value == temp->value)
				error();
			temp = temp->next;
		}
	}
}
