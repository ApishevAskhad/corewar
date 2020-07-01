/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_players_nbrs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:48:24 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/16 22:51:10 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	main()
{
	t_game  game;
	
	ft_printf("players_nbr == 0:\n");
	ft_bzero(&game, sizeof(t_game));
	check_players_nbrs(game);
	
	ft_printf("\nplayers_nbr == 3, players with number 1-3 are blank:\n");
	game.players_nbr = 3;
	check_players_nbrs(game);

	ft_printf("\nplayers_nbr == 3, players with number 1 and 3 are blank:\n");
	game.players[1].magic = COREWAR_EXEC_MAGIC;
	check_players_nbrs(game);

	game.players[0].magic = COREWAR_EXEC_MAGIC;
	game.players[2].magic = COREWAR_EXEC_MAGIC;
	ft_printf("\nplayers_nbr == 3, all players from 1 to 3 are exist:\n");
	check_players_nbrs(game);
}
