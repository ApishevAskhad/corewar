/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_introduce_winner_format.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:03:59 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/01 00:50:37 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
* Run test_introduce_winner.sh
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
	game.alive = 1;
	introduce_winner(game);
	return (0);
}
