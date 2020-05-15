/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:43:01 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/15 03:40:49 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_timers(t_game *game)
{
	game->timers[OP_LV - 1] = 10;
	game->timers[OP_LD - 1] = 5;
	game->timers[OP_ST - 1] = 5;
	game->timers[OP_ADD - 1] = 10;
	game->timers[OP_SUB - 1] = 10;
	game->timers[OP_AND - 1] = 6;
	game->timers[OP_OR - 1] = 6;
	game->timers[OP_XOR - 1] = 6;
	game->timers[OP_ZJMP - 1] = 20;
	game->timers[OP_LDI - 1] = 25;
	game->timers[OP_STI - 1] = 25;
	game->timers[OP_FORK - 1] = 800;
	game->timers[OP_LLD - 1] = 10;
	game->timers[OP_LLDI - 1] = 50;
	game->timers[OP_LFORK - 1] = 1000;
	game->timers[OP_AFF - 1] = 2;
}

void	init_args_size(t_game *game)
{
	game->args_sizes[OP_LV - 1] = 1;
	game->args_sizes[OP_LD - 1] = 2;
	game->args_sizes[OP_ST - 1] = 2;
	game->args_sizes[OP_ADD - 1] = 3;
	game->args_sizes[OP_SUB - 1] = 3;
	game->args_sizes[OP_AND - 1] = 3;
	game->args_sizes[OP_OR - 1] = 3;
	game->args_sizes[OP_XOR - 1] = 3;
	game->args_sizes[OP_ZJMP - 1] = 1;
	game->args_sizes[OP_LDI - 1] = 3;
	game->args_sizes[OP_STI - 1] = 3;
	game->args_sizes[OP_FORK - 1] = 1;
	game->args_sizes[OP_LLD - 1] = 2;
	game->args_sizes[OP_LLDI - 1] = 3;
	game->args_sizes[OP_LFORK - 1] = 1;
	game->args_sizes[OP_AFF - 1] = 1;
}

void	init_dir_size(t_game *game)
{
	game->dir_sizes[OP_LV - 1] = DIR_SIZE;
	game->dir_sizes[OP_LD - 1] = DIR_SIZE;
	game->dir_sizes[OP_ST - 1] = DIR_SIZE;
	game->dir_sizes[OP_ADD - 1] = DIR_SIZE;
	game->dir_sizes[OP_SUB - 1] = DIR_SIZE;
	game->dir_sizes[OP_AND - 1] = DIR_SIZE;
	game->dir_sizes[OP_OR - 1] = DIR_SIZE;
	game->dir_sizes[OP_XOR - 1] = DIR_SIZE;
	game->dir_sizes[OP_ZJMP - 1] = IND_SIZE;
	game->dir_sizes[OP_LDI - 1] = IND_SIZE;
	game->dir_sizes[OP_STI - 1] = IND_SIZE;
	game->dir_sizes[OP_FORK - 1] = IND_SIZE;
	game->dir_sizes[OP_LLD - 1] = DIR_SIZE;
	game->dir_sizes[OP_LLDI - 1] = IND_SIZE;
	game->dir_sizes[OP_LFORK - 1] = IND_SIZE;
	game->dir_sizes[OP_AFF - 1] = DIR_SIZE;
}

void	init_operations(t_game *game)
{
	game->operations[OP_LV - 1] = op_live;
	game->operations[OP_LD - 1] = op_ld;
	game->operations[OP_ST - 1] = op_st;
	game->operations[OP_ADD - 1] = op_add;
	game->operations[OP_SUB - 1] = op_sub;
	game->operations[OP_AND - 1] = op_and;
	game->operations[OP_OR - 1] = op_or;
	game->operations[OP_XOR - 1] = op_xor;
	game->operations[OP_ZJMP - 1] = op_zjmp;
	game->operations[OP_LDI - 1] = op_ldi;
	game->operations[OP_STI - 1] = op_sti;
	game->operations[OP_FORK - 1] = op_fork;
	game->operations[OP_LLD - 1] = op_lld;
	game->operations[OP_LLDI - 1] = op_lldi;
	game->operations[OP_LFORK - 1] = op_lfork;
	game->operations[OP_AFF - 1] = op_aff;
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
