/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:48:55 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/12 21:56:36 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int main()
{
	t_carry list[4];

	ft_bzero(list, sizeof(t_carry) * 4);
	assert(del_carry(&list[0], 0) == NULL);

	ft_printf("{green}OK{eoc} {yellow}*new_cary(int nbr);{eoc}\n");
	ft_printf("{green}OK{eoc} {yellow}push_carry(t_carry **head, int nbr);{eoc}\n");
	ft_printf("{green}OK{eoc} {yellow}*del_carry(t_carry *carry, int nbr);{eoc}\n");
	return (0);
}