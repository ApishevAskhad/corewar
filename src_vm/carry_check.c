/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carry_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:22:34 by slindgre          #+#    #+#             */
/*   Updated: 2020/06/04 23:46:52 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			check_op_code(int op_code)
{
	if (0 < op_code && op_code <= OPS_SIZE)
		return (TRUE);
	return (FALSE);
}

static int	check_arg_code(uint8_t arg_code)
{
	return (REG_CODE <= arg_code && arg_code <= IND_CODE);
}

static int	check_args_code_helper(t_carry *carry, uint8_t op_code,
uint8_t args_code)
{
	uint8_t a1;
	uint8_t a2;
	uint8_t a3;

	a1 = carry->arg_types[0];
	a2 = carry->arg_types[1];
	a3 = carry->arg_types[2];
	(void)args_code;
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

int			check_args_code(t_carry *carry, uint8_t op_code, uint8_t args_code)
{
	carry->arg_types[0] = args_code >> 6;
	carry->arg_types[1] = (args_code >> 4) & 3;
	carry->arg_types[2] = (args_code >> 2) & 3;
	if (op_code == OP_LV || op_code == OP_ZJMP || op_code == OP_FORK ||
	op_code == OP_LFORK)
		return (TRUE);
	if (op_code == OP_AFF && carry->arg_types[0] == REG_CODE)
		return (TRUE);
	if (op_code == OP_ST && carry->arg_types[0] == REG_CODE &&
	(carry->arg_types[1] == REG_CODE || carry->arg_types[1] == IND_CODE))
		return (TRUE);
	if ((op_code == OP_ADD || op_code == OP_SUB) && (args_code & 0xfc) == 0x54)
		return (TRUE);
	if ((op_code == OP_LD || op_code == OP_LLD) &&
	((args_code & 0xf0) == 0x90 || (args_code & 0xf0) == 0xd0))
		return (TRUE);
	return (check_args_code_helper(carry, op_code, args_code));
}
