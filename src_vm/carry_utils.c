/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carry_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 21:22:34 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/02 01:05:50 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	check_op_code(UC op_code)
{
	if (0 < op_code && op_code <= 16)
		return (TRUE);
	return (FALSE);
}

int check_arg_code(UC arg_code)
{
	return (REG_CODE <= arg_code && arg_code <= IND_CODE);
}

int check_args_code_helper(UC op_code, UC args_code)
{
	UC a1;
	UC a2;
	UC a3;

	a1 = args_code >> 6;
	a2 = (args_code >> 4) & 3;
	a3 = (args_code >> 2) & 3;
	if ((args_code & 3) != 0)
		return (FALSE);
	if ((op_code == 6 || op_code == 7 || op_code == 8 || op_code == 10
	|| op_code == 14) && check_arg_code(a1) && check_arg_code(a2) &&
	a3 == REG_CODE && !((op_code == 10 || op_code == 14) && a2 == IND_CODE))
		return (TRUE);
	if (op_code == 11 && a1 == REG_CODE && check_arg_code(a2) &&
	REG_CODE <= a3 && a3 <= DIR_CODE)
		return (TRUE);
	return (FALSE);
}

int	check_args_code(UC op_code, UC args_code)
{
	if (op_code == 1 || op_code == 9 || op_code == 12 || op_code == 15)
		return (TRUE);
	if (op_code == 16 && args_code == 0x40)
		return (TRUE);
	if (op_code == 3 && (args_code == 0x50 || args_code == 0x70))
		return (TRUE);
	if ((op_code == 4 || op_code == 5) && args_code == 0x54)
		return (TRUE);
	if ((op_code == 2 || op_code == 13) &&
	(args_code == 0x90 || args_code == 0xd0))
		return (TRUE);
	return (check_args_code_helper(op_code, args_code));
}

int check_op_arguments(unsigned char *op_str)
{
	assert(op_str != NULL);

	if (!check_op_code(op_str[0]) || !check_args_code(op_str[0], op_str[1]))
	{
		return (FALSE);
	}
	return (TRUE);
}
