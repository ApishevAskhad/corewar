/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:27:53 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/12 22:10:24 by slindgre         ###   ########.fr       */
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

void	push_carry(t_carry **head, int nbr)
{
	assert(head != NULL);
	t_carry *new;

	new = new_carry(nbr);
	new->next = *head;
	*head = new;
}

t_carry *del_carry(t_carry *carry, int nbr)
{
	t_carry *next_carry;

	if (carry == NULL)
		return (NULL);
	if (carry->nbr == nbr) {
		next_carry = carry->next;
		free(carry);
		return (next_carry);
	}
	carry->next = del_carry(carry->next, nbr);
	return (carry);
}