/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_introduce.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:03:59 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/13 19:40:36 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
* Run test_introduce.sh
*/

int main()
{
    t_game  game;
    char    *pl_1;
    char    *pl_2;
    char    *pl_3;
    char    *pl_4;

    game.players_nbr = 1;
    pl_1 = "resources/champs/Gagnant.cor";
    game.players[0] = create_player(pl_1);
    introduce_players(game);
    
    game.players_nbr = 2;
    pl_2 = "resources/champs/maxidef.cor";
    game.players[1] = create_player(pl_2);
    introduce_players(game);
    
    game.players_nbr = 3;
    pl_3 = "resources/champs/maxidef.cor";
    game.players[2] = create_player(pl_3);
    introduce_players(game);
    
    game.players_nbr = 4;
    pl_4 = "resources/champs/Gagnant.cor";
    game.players[3] = create_player(pl_4);
    introduce_players(game);
    return (0);
}
