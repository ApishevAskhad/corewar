/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:27:53 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/14 21:40:13 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_carry	*new_carry(int nbr)
{
	t_carry	*carry;

	if (!(carry = ft_memalloc(sizeof(t_carry))))
		return (NULL);
	carry->nbr = nbr;
	return (carry);
}

int		push_carry(t_carry **head, int nbr)
{
	assert(head != NULL);
	t_carry *new;

	if (!(new = new_carry(nbr)))
		return (0);
	new->next = *head;
	*head = new;
	return (1);
}

t_carry	*del_carry(t_carry *carry, int nbr)
{
	t_carry *next_carry;

	if (carry == NULL)
		return (NULL);
	if (carry->nbr == nbr)
	{
		next_carry = carry->next;
		free(carry);
		return (next_carry);
	}
	carry->next = del_carry(carry->next, nbr);
	return (carry);
}
