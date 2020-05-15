/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 01:50:10 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/15 03:35:48 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_sub(t_game *game, t_carry *carry)
{
	int res;	
	
	if (game != NULL)
	{
		res = carry->r[carry->args[0] - 1] - carry->r[carry->args[1] - 1];
		carry->r[carry->args[2] - 1] = res;
		carry->carry = 0;
		if (res == 0)
			carry->carry = 1;
	}
}

void	op_and(t_game *game, t_carry *carry)
{
	int res;
	int	arg1;
	int arg2;
	int	pos;

	arg1 = carry->r[carry->args[0] - 1];
	arg2 = carry->r[carry->args[1] - 1];
	if (carry->arg_types[0] == T_DIR)
		arg1 = carry->args[0];
	if (carry->arg_types[1] == T_DIR)
		arg2 = carry->args[1];
	if (carry->arg_types[0] == T_IND)
	{
		pos = carry->pos + carry->args[0] % IDX_MOD;
		arg1 = read_n_bytes_from_mem(game, pos, REG_SIZE);
	}
	if (carry->arg_types[1] == T_IND)
	{
		pos = carry->pos + carry->args[1] % IDX_MOD;
		arg2 = read_n_bytes_from_mem(game, pos, REG_SIZE);
	}
	res = arg1 & arg2;
	carry->r[carry->args[2] - 1] = res;
	carry->carry = 0;
	if (res == 0)
		carry->carry = 1;
}

void	op_or(t_game *game, t_carry *carry)
{
	int res;
	int	arg1;
	int arg2;
	int	pos;

	arg1 = carry->r[carry->args[0] - 1];
	arg2 = carry->r[carry->args[1] - 1];
	if (carry->arg_types[0] == T_DIR)
		arg1 = carry->args[0];
	if (carry->arg_types[1] == T_DIR)
		arg2 = carry->args[1];
	if (carry->arg_types[0] == T_IND)
	{
		pos = carry->pos + carry->args[0] % IDX_MOD;
		arg1 = read_n_bytes_from_mem(game, pos, REG_SIZE);
	}
	if (carry->arg_types[1] == T_IND)
	{
		pos = carry->pos + carry->args[1] % IDX_MOD;
		arg2 = read_n_bytes_from_mem(game, pos, REG_SIZE);
	}
	res = arg1 | arg2;
	carry->r[carry->args[2] - 1] = res;
	carry->carry = 0;
	if (res == 0)
		carry->carry = 1;
}

void	op_xor(t_game *game, t_carry *carry)
{
	int res;
	int	arg1;
	int arg2;
	int	pos;

	arg1 = carry->r[carry->args[0] - 1];
	arg2 = carry->r[carry->args[1] - 1];
	if (carry->arg_types[0] == T_DIR)
		arg1 = carry->args[0];
	if (carry->arg_types[1] == T_DIR)
		arg2 = carry->args[1];
	if (carry->arg_types[0] == T_IND)
	{
		pos = carry->pos + carry->args[0] % IDX_MOD;
		arg1 = read_n_bytes_from_mem(game, pos, REG_SIZE);
	}
	if (carry->arg_types[1] == T_IND)
	{
		pos = carry->pos + carry->args[1] % IDX_MOD;
		arg2 = read_n_bytes_from_mem(game, pos, REG_SIZE);
	}
	res = arg1 ^ arg2;
	carry->r[carry->args[2] - 1] = res;
	carry->carry = 0;
	if (res == 0)
		carry->carry = 1;
}
