/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carry_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:22:34 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/16 04:52:39 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	check_op_code(int op_code)
{
	if (0 < op_code && op_code <= OPS_SIZE)
		return (TRUE);
	return (FALSE);
}

int	check_reg_number(int reg_num)
{
	if (0 < reg_num && reg_num <= REG_NUMBER)
		return (TRUE);
	return (FALSE);
}

int	check_arg_code(UC arg_code)
{
	return (REG_CODE <= arg_code && arg_code <= IND_CODE);
}

int	check_args_code_helper(t_carry *carry, UC op_code, UC args_code)
{
	UC a1;
	UC a2;
	UC a3;

	a1 = carry->arg_types[0];
	a2 = carry->arg_types[1];
	a3 = carry->arg_types[2];
	if ((args_code & 3) != 0)
		return (FALSE);
	if ((op_code == OP_AND || op_code == OP_OR || op_code == OP_XOR ||
	op_code == OP_LDI || op_code == OP_LLDI) &&
	check_arg_code(a1) && check_arg_code(a2) && a3 == REG_CODE &&
	!((op_code == 10 || op_code == 14) && a2 == IND_CODE))
		return (TRUE);
	if (op_code == OP_STI && a1 == REG_CODE && check_arg_code(a2) &&
	REG_CODE <= a3 && a3 <= DIR_CODE)
		return (TRUE);
	return (FALSE);
}

int	check_args_code(t_carry *carry, UC op_code, UC args_code)
{
	carry->arg_types[0] = args_code >> 6;
	carry->arg_types[1] = (args_code >> 4) & 3;
	carry->arg_types[2] = (args_code >> 2) & 3;
	
	if (op_code == OP_LV || op_code == OP_ZJMP || op_code == OP_FORK ||
	op_code == OP_LFORK)
		return (TRUE);
	if (op_code == OP_AFF && args_code == 0x40)
		return (TRUE);
	if (op_code == OP_ST && (args_code == 0x50 || args_code == 0x70))
		return (TRUE);
	if ((op_code == OP_ADD || op_code == OP_SUB) && args_code == 0x54)
		return (TRUE);
	if ((op_code == OP_LD || op_code == OP_LLD) &&
	(args_code == 0x90 || args_code == 0xd0))
		return (TRUE);
	return (check_args_code_helper(carry, op_code, args_code));
}

int	set_carry_args(t_game *game, t_carry *carry)
{
	int	i;
	int	res;
	int	pos;
	UC	args_code;
	UC	arg_code;

	args_code = game->mem[(carry->pos + 1) % MEM_SIZE];
	res = TRUE;
	carry->jump = 2;
	if (carry->op == OP_LV || carry->op == OP_ZJMP || carry->op == OP_FORK ||
	carry->op == OP_LFORK)
	{
		carry->jump -= 1;
		args_code = 0x80;
	}
	i = 0;
	while (i < game->args_sizes[carry->op - 1])
	{
		arg_code = (args_code >> (CHAR_BIT - (i + 1) * 2)) & 3;
		pos = (MEM_SIZE + carry->pos + carry->jump) % MEM_SIZE;
		if (arg_code == REG_CODE)
		{
			carry->args[i] = read_n_bytes_from_mem(game, pos, 1);
			if (check_reg_number(carry->args[i]) == FALSE)
				res = FALSE;
			carry->jump += 1;
		}
		if (arg_code == IND_CODE)
		{
			carry->args[i] = read_2_bytes_from_mem(game, pos);
			carry->jump += IND_SIZE;
		}
		if (arg_code == DIR_CODE)
		{
			carry->args[i] = read_2_bytes_from_mem(game, pos);
			if (game->dir_sizes[carry->op - 1] == DIR_SIZE)
				carry->args[i] = read_n_bytes_from_mem(game, pos, DIR_SIZE);
			carry->jump += game->dir_sizes[carry->op - 1];
		}
		i++;
	}
	return (res);
}
