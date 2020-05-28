/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 01:50:15 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/24 22:21:27 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_zjmp(t_game *game, t_carry *carry)
{
	if (carry->carry == 1 && game != NULL)
	{
		carry->pos = (MEM_SIZE + carry->pos + (carry->args[0] % IDX_MOD))
		% MEM_SIZE;
		carry->jump = 0;
	}
	if (game->v & LOG_OPERATIONS)
	{
		ft_printf("P %4d | zjmp %d %s\n",
		carry->id, carry->args[0], (carry->carry) ? "OK" : "FAILED");
	}
}

void	op_ldi(t_game *game, t_carry *carry)
{
	int	arg1;
	int	arg2;
	int	pos;

	arg1 = carry->args[0];
	arg2 = carry->args[1];
	if (carry->arg_types[0] == REG_CODE)
		arg1 = carry->r[carry->args[0] - 1];
	if (carry->arg_types[1] == REG_CODE)
		arg2 = carry->r[carry->args[1] - 1];
	if (carry->arg_types[0] == IND_CODE)
	{
		pos = MEM_SIZE + carry->pos + (carry->args[0] % IDX_MOD);
		arg1 = read_4_bytes_from_mem(game, pos);
	}
	pos = MEM_SIZE + carry->pos + ((arg1 + arg2) % IDX_MOD);
	carry->r[carry->args[2] - 1] = read_4_bytes_from_mem(game, pos);
	if (game->v & LOG_OPERATIONS)
	{
		ft_printf("P %4d | ldi %d %d r%d\n",
		carry->id, arg1, arg2, carry->args[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc and mod %d)\n",
		arg1, arg2, arg1 + arg2, carry->pos + (arg1 + arg2) % IDX_MOD);
	}
}

void	op_sti(t_game *game, t_carry *carry)
{
	int	arg1;
	int	arg2;
	int	arg3;
	int	pos;

	arg1 = carry->r[carry->args[0] - 1];
	arg2 = carry->args[1];
	arg3 = carry->args[2];
	if (carry->arg_types[1] == REG_CODE)
		arg2 = carry->r[carry->args[1] - 1];
	if (carry->arg_types[2] == REG_CODE)
		arg3 = carry->r[carry->args[2] - 1];
	if (carry->arg_types[1] == IND_CODE)
	{
		pos = MEM_SIZE + carry->pos + (carry->args[1] % IDX_MOD);
		arg2 = read_4_bytes_from_mem(game, pos);
	}
	write_4_bytes_to_mem(game, carry->pos + ((arg2 + arg3) % IDX_MOD), arg1);
	if (game->v & LOG_OPERATIONS)
	{
		ft_printf("P %4d | sti r%d %d %d\n",
		carry->id, carry->args[0], arg2, arg3);
		ft_printf("       | -> store to %d + %d = %d (with pc and mod %d)\n",
		arg2, arg3, arg2 + arg3, carry->pos + ((arg2 + arg3) % IDX_MOD));
	}
}

void	op_fork(t_game *game, t_carry *carry)
{
	t_carry *new;
	int		addr;

	addr = carry->pos + (carry->args[0] % IDX_MOD);
	new = new_carry(0, addr);
	new->carry = carry->carry;
	new->live = carry->live;
	ft_memcpy(new->r, carry->r, REG_SIZE * REG_NUMBER);
	new->next = game->carries;
	game->carries = new;
	if (game->v & LOG_OPERATIONS)
	{
		ft_printf("P %4d | fork %d (%d)\n",
		carry->id, carry->args[0], addr);
	}
}
