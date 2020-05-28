/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 00:06:09 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/24 22:22:41 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_live(t_game *game, t_carry *carry)
{
	carry->live = game->cycles;
	game->lives += 1;
	if (game->v & LOG_OPERATIONS)
	{
		ft_printf("P %4d | live %d\n",
		carry->id, carry->args[0]);
	}
	if (carry->args[0] < 0 && -carry->args[0] <= game->players_nbr)
	{
		game->alive = -carry->args[0];
		if (game->v & LOG_LIVES)
			ft_printf("Player %d (%s) is said to be alive\n",
			-carry->args[0], game->players[-carry->args[0] - 1].prog_name);
	}
}

void	op_ld(t_game *game, t_carry *carry)
{
	int	pos;
	int	res;

	if (carry->arg_types[0] == DIR_CODE)
	{
		res = carry->args[0];
	}
	else
	{
		pos = MEM_SIZE + carry->pos + (carry->args[0] % IDX_MOD);
		res = read_4_bytes_from_mem(game, pos);
	}
	carry->r[carry->args[1] - 1] = res;
	carry->carry = 0;
	if (res == 0)
		carry->carry = 1;
	if (game->v & LOG_OPERATIONS)
	{
		ft_printf("P %4d | ld %d r%d\n",
		carry->id, res, carry->args[1]);
	}
}

void	op_st(t_game *game, t_carry *carry)
{
	int	pos;
	int res;

	res = carry->r[carry->args[0] - 1];
	if (carry->arg_types[1] == REG_CODE)
	{
		carry->r[carry->args[1] - 1] = res;
	}
	else
	{
		pos = MEM_SIZE + carry->pos + (carry->args[1] % IDX_MOD);
		write_4_bytes_to_mem(game, pos, res);
	}
	if (game->v & LOG_OPERATIONS)
	{
		ft_printf("P %4d | st r%d %d\n",
		carry->id, carry->args[0], carry->args[1]);
	}
}

void	op_add(t_game *game, t_carry *carry)
{
	int res;

	res = carry->r[carry->args[0] - 1] + carry->r[carry->args[1] - 1];
	carry->r[carry->args[2] - 1] = res;
	carry->carry = 0;
	if (res == 0)
		carry->carry = 1;
	if (game->v & LOG_OPERATIONS)
	{
		ft_printf("P %4d | add r%d r%d r%d\n",
		carry->id, carry->args[0], carry->args[1], carry->args[2]);
	}
}
