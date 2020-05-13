/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: status <status@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 21:43:42 by gloras-t          #+#    #+#             */
/*   Updated: 2020/05/13 05:22:31 by status           ###   ########.fr       */
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
	main_cycle(&game, carry);
	introduce_winner(game);
	
	return (0);
}
