/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_introduce.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:03:59 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/13 20:38:54 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
* Run test_introduce.sh
*/

int main(int ac, char **av)
{
    t_game  game;

    int i = 1;
    game.players_nbr = ac - 1;
    while (i < ac)
    {
        game.players[i - 1] = create_player(av[i]);
        i++;
    }
    introduce_players(game);
    return (0);
}
