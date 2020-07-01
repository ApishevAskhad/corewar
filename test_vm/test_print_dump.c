/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_print_dump_32.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:17:35 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/02 23:48:46 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int main()
{
    int     size_zero = 2048;
    UC    test_zero[size_zero];
    ft_bzero(test_zero, size_zero);

    int     size_champ = 3000;
    UC    test_champ[size_champ];
    read(open("resources/champs/Gagnant.cor", O_RDONLY), test_champ, size_champ);

    ft_printf("Test blank dump, size: %d\n", size_zero);
    print_dump_32(test_zero, size_zero);

     ft_printf("\nTest dump of champ file, size: %d\n", size_champ);
    print_dump_32(test_champ, size_champ);
    return (0);
}