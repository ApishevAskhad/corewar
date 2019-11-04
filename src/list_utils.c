/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 20:27:53 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/04 21:35:41 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_carry     *new_cary(int nbr)
{
	t_carry	*carry;

	if (!(carry = ft_memalloc(sizeof(t_carry))))
		return (NULL);
    carry->nbr = nbr;
	return (carry);
}

void		push_carry(t_carry **head, int nbr)
{
    assert (head != NULL);
	t_carry *new;
    
	new = new_node(nbr);
	new->next = *head;
	*head = new;
}

void		del_carry(t_carry **head, int nbr)
{
	t_carry *tmp;

	if (head && *head)
	{
		while (*head)
		{
            if ((*head)->nbr == nbr)
            {
                break;
            }
            *head = (*head)->next;
		}
	}
}