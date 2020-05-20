/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:27:53 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/17 03:06:55 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_carry	*new_carry(int nbr, int position)
{
	t_carry		*carry;
	static int	id;

	if (!(carry = ft_memalloc(sizeof(t_carry))))
		return (NULL);
	carry->id = ++id;
	carry->r[0] = nbr;
	carry->pos = (MEM_SIZE + position) % MEM_SIZE;
	return (carry);
}

int		push_carry(t_carry **head, int nbr, int position)
{
	t_carry *new;

	assert(head != NULL);
	if (!(new = new_carry(nbr, position)))
		return (0);
	new->next = *head;
	*head = new;
	return (1);
}

void	del_carry(t_carry **carry, t_carry *needle)
{
	t_carry *tmp;
	t_carry	*prev;

	tmp = *carry;
	prev = NULL;
	while (tmp)
	{
		if (tmp == needle)
		{
			if (!prev)
			{
				*carry = tmp->next;
			}
			else
			{
				prev->next = tmp->next;
			}
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
