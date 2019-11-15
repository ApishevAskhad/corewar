/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 21:48:55 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/14 21:38:28 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int main()
{
	t_carry *list;
	t_carry *temp;

	list = new_carry(1);
	assert(list);
	assert(list->nbr == 1);
	assert(list->next == NULL);
	free(list);
	ft_printf("{green}OK{eoc} {yellow}*new_cary(int nbr);{eoc}\n");

	list = NULL;
	push_carry(&list, 2);
	assert(list != NULL);
	assert(list->nbr == 2);
	assert(list->next == NULL);

	temp = list;
	push_carry(&list, 3);
	assert(list != NULL);
	assert(list->nbr == 3);
	assert(list->next == temp);
	ft_printf("{green}OK{eoc} {yellow}push_carry(t_carry **head, int nbr);{eoc}\n");

	list = del_carry(list, 3);
	assert(list == temp);
	list = del_carry(list, 2);
	assert(list == NULL);
	ft_printf("{green}OK{eoc} {yellow}*del_carry(t_carry *carry, int nbr);{eoc}\n");
	return (0);
}