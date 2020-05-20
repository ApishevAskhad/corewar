/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:43:42 by gloras-t          #+#    #+#             */
/*   Updated: 2020/05/19 02:39:18 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		main(int argc, char *argv[])
{
	t_game	game;
	t_carry *carry;

	carry = NULL;
	init_game(&game);
	parse_args(argc, argv, &game);
	introduce_players(game);
	place_players_code(&game, &carry);
	game.carries = carry;
	game.alive = game.players_nbr;
	main_cycle(&game);
	introduce_winner(game);
	free_carry_list(game.carries);
	return (0);
}
