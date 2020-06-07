/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 01:50:10 by slindgre          #+#    #+#             */
/*   Updated: 2020/06/04 23:52:12 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_sub(t_game *game, t_carry *carry)
{
	int32_t res;

	if (game != NULL)
	{
		res = carry->r[carry->args[0] - 1] - carry->r[carry->args[1] - 1];
		carry->r[carry->args[2] - 1] = res;
		carry->carry = 0;
		if (res == 0)
			carry->carry = 1;
	}
	if (game->v & LOG_OPERATIONS)
	{
		ft_printf("P %4d | sub r%d r%d r%d\n",
		carry->id, carry->args[0], carry->args[1], carry->args[2]);
	}
}

void	op_and(t_game *game, t_carry *carry)
{
	int32_t	arg1;
	int32_t arg2;
	int		pos;

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
	if (carry->arg_types[1] == IND_CODE)
	{
		pos = MEM_SIZE + carry->pos + (carry->args[1] % IDX_MOD);
		arg2 = read_4_bytes_from_mem(game, pos);
	}
	carry->r[carry->args[2] - 1] = arg1 & arg2;
	carry->carry = (carry->r[carry->args[2] - 1] == 0) ? 1 : 0;
	if (game->v & LOG_OPERATIONS)
		ft_printf("P %4d | and %d %d r%d\n",
		carry->id, arg1, arg2, carry->args[2]);
}

void	op_or(t_game *game, t_carry *carry)
{
	int32_t	arg1;
	int32_t arg2;
	int		pos;

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
	if (carry->arg_types[1] == IND_CODE)
	{
		pos = MEM_SIZE + carry->pos + (carry->args[1] % IDX_MOD);
		arg2 = read_4_bytes_from_mem(game, pos);
	}
	carry->r[carry->args[2] - 1] = arg1 | arg2;
	carry->carry = (carry->r[carry->args[2] - 1] == 0) ? 1 : 0;
	if (game->v & LOG_OPERATIONS)
		ft_printf("P %4d | or %d %d r%d\n",
		carry->id, arg1, arg2, carry->args[2]);
}

void	op_xor(t_game *game, t_carry *carry)
{
	int32_t	arg1;
	int32_t arg2;
	int		pos;

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
	if (carry->arg_types[1] == IND_CODE)
	{
		pos = MEM_SIZE + carry->pos + (carry->args[1] % IDX_MOD);
		arg2 = read_4_bytes_from_mem(game, pos);
	}
	carry->r[carry->args[2] - 1] = arg1 ^ arg2;
	carry->carry = (carry->r[carry->args[2] - 1] == 0) ? 1 : 0;
	if (game->v & LOG_OPERATIONS)
		ft_printf("P %4d | xor %d %d r%d\n",
		carry->id, arg1, arg2, carry->args[2]);
}
