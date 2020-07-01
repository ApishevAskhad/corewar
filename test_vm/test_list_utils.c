/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:48:55 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/13 20:30:16 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int main()
{
	t_carry *list;
	t_carry *temp;

	list = new_carry(-1, 0);
	assert(list);
	assert(list->r[0] == -1);
	assert(list->next == NULL);
	free(list);
	ft_printf("{green}OK{eoc} {yellow}*new_cary(int nbr);{eoc}\n");

	list = NULL;
	push_carry(&list, -2, 0);
	assert(list != NULL);
	assert(list->r[0] == -2);
	assert(list->next == NULL);

	temp = list;
	push_carry(&list, -3, 0);
	assert(list != NULL);
	assert(list->r[0] == -3);
	assert(list->next == temp);
	ft_printf("{green}OK{eoc} {yellow}push_carry(t_carry **head, int nbr);{eoc}\n");

	list = del_carry(list, list);
	assert(list == temp);
	list = del_carry(list, list);
	assert(list == NULL);
	ft_printf("{green}OK{eoc} {yellow}*del_carry(t_carry *carry, int nbr);{eoc}\n");
	return (0);
}