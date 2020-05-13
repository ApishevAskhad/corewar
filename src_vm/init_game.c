/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: status <status@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:43:01 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/13 05:26:38 by status           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		init_timers(t_game *game)
{
	game->timers[0] = 10;
	game->timers[1] = 5;
	game->timers[2] = 5;
	game->timers[3] = 10;
	game->timers[4] = 10;
	game->timers[5] = 6;
	game->timers[6] = 6;
	game->timers[7] = 6;
	game->timers[8] = 20;
	game->timers[9] = 25;
	game->timers[10] = 25;
	game->timers[11] = 800;
	game->timers[12] = 10;
	game->timers[13] = 50;
	game->timers[14] = 1000;
	game->timers[15] = 2;
}

void	init_args_size(t_game *game)
{
	game->args_sizes[0] = 1;
	game->args_sizes[1] = 2;
	game->args_sizes[2] = 2;
	game->args_sizes[3] = 3;
	game->args_sizes[4] = 3;
	game->args_sizes[5] = 3;
	game->args_sizes[6] = 3;
	game->args_sizes[7] = 3;
	game->args_sizes[8] = 1;
	game->args_sizes[9] = 3;
	game->args_sizes[10] = 3;
	game->args_sizes[11] = 1;
	game->args_sizes[12] = 2;
	game->args_sizes[13] = 3;
	game->args_sizes[14] = 1;
	game->args_sizes[15] = 1;
}

void	init_dir_size(t_game *game)
{
	game->dir_sizes[0] = DIR_SIZE;
	game->dir_sizes[1] = DIR_SIZE;
	game->dir_sizes[2] = DIR_SIZE;
	game->dir_sizes[3] = DIR_SIZE;
	game->dir_sizes[4] = DIR_SIZE;
	game->dir_sizes[5] = DIR_SIZE;
	game->dir_sizes[6] = DIR_SIZE;
	game->dir_sizes[7] = DIR_SIZE;
	game->dir_sizes[8] = IND_SIZE;
	game->dir_sizes[9] = IND_SIZE;
	game->dir_sizes[10] = IND_SIZE;
	game->dir_sizes[11] = IND_SIZE;
	game->dir_sizes[12] = DIR_SIZE;
	game->dir_sizes[13] = IND_SIZE;
	game->dir_sizes[14] = IND_SIZE;
	game->dir_sizes[15] = DIR_SIZE;
}

void	init_operations(t_game *game)
{
	// TODO: fill with correspond functions
	game->operations[0] = op_live;
	game->operations[1] = op_live;
	game->operations[2] = op_live;
	game->operations[3] = op_live;
	game->operations[4] = op_live;
	game->operations[5] = op_live;
	game->operations[6] = op_live;
	game->operations[7] = op_live;
	game->operations[8] = op_live;
	game->operations[9] = op_live;
	game->operations[10] = op_live;
	game->operations[11] = op_live;
	game->operations[12] = op_live;
	game->operations[13] = op_live;
	game->operations[14] = op_live;
	game->operations[15] = op_live;
}

void	init_game(t_game *game)
{
	assert(game != NULL);
	ft_bzero(game, sizeof(t_game));
	game->dump = OFF;
	game->cycle_to_die = CYCLE_TO_DIE;
	init_timers(game);
	init_args_size(game);
	init_dir_size(game);
	init_operations(game);
}
