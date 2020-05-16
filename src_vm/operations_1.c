/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 00:06:09 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/16 03:07:46 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_live(t_game *game, t_carry *carry)
{
	carry->live = game->cycles;
	game->lives += 1;
	if (carry->args[0] < 0 && -carry->args[0] <= game->players_nbr)
		game->alive = -carry->args[0];
}

void	op_ld(t_game *game, t_carry *carry)
{
	int	pos;
	int	res;

	if (carry->arg_types[0] == T_DIR)
	{
		res = carry->args[0];
	}
	else
	{
		pos = MEM_SIZE + carry->pos + (carry->args[0] % IDX_MOD);
		res = read_n_bytes_from_mem(game, pos, REG_SIZE);
	}
	carry->r[carry->args[1] - 1] = res;
	carry->carry = 0;
	if (res == 0)
		carry->carry = 1;
}

void	op_st(t_game *game, t_carry *carry)
{
	int	pos;
	int res;
	
	res = carry->r[carry->args[0] - 1];;
	if (carry->arg_types[1] == T_REG)
	{
		carry->r[carry->args[1] - 1] = res;
	}
	else
	{
		pos = MEM_SIZE + carry->pos + (carry->args[1] % IDX_MOD);
		write_4bytes_to_mem(game, pos, res);
	}
}

void	op_add(t_game *game, t_carry *carry)
{
	int res;

	if (game != NULL)
	{
		res = carry->r[carry->args[0] - 1] + carry->r[carry->args[1] - 1];
		carry->r[carry->args[2] - 1] = res;
		carry->carry = 0;
		if (res == 0)
			carry->carry = 1;
	}
}
