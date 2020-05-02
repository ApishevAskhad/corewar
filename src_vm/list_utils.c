/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:27:53 by slindgre          #+#    #+#             */
/*   Updated: 2020/04/30 22:11:48 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_carry	*new_carry(int nbr, int position)
{
	t_carry	*carry;

	if (!(carry = ft_memalloc(sizeof(t_carry))))
		return (NULL);
	carry->r[0] = nbr;
	carry->pos = position % MEM_SIZE;
	return (carry);
}

int		push_carry(t_carry **head, int nbr, int position)
{
	assert(head != NULL);
	t_carry *new;

	if (!(new = new_carry(nbr, position)))
		return (0);
	new->next = *head;
	*head = new;
	return (1);
}

t_carry	*del_carry(t_carry *carry, t_carry *needle)
{
	t_carry *next_carry;

	if (carry == NULL)
		return (NULL);
	if (carry == needle)
	{
		next_carry = carry->next;
		free(carry);
		return (next_carry);
	}
	carry->next = del_carry(carry->next, needle);
	return (carry);
}
