/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:15:22 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/19 02:38:40 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	destroy(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	free_carry_list(t_carry *carry)
{
	t_carry	*tmp;

	while (carry)
	{
		tmp = carry;
		carry = carry->next;
		free(tmp);
	}
}