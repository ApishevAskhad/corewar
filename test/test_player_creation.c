/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_player_creation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 22:17:35 by slindgre          #+#    #+#             */
/*   Updated: 2019/10/31 22:10:23 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int main()
{
    char    *players[4] = {"42.cor", "Gagnant.cor", "maxidef.cor", "toto.cor"};
    char    pref[] = "resources/champs/";
    int     i = 0;
    t_player player;
    
	while (i < 4) {
        player = create_player(ft_strjoin(pref, players[i]));
        ft_printf("\n%#x\n", player.magic);
        ft_printf("Name: %s\n", player.prog_name);
        ft_printf("Size: %lu\n", player.prog_size);
        ft_printf("Comm: %s\n", player.comment);
        ft_printf("Exec code:\n");
        print_hexdump(player.code, player.prog_size);
        i++;
    }
    return (0);
}