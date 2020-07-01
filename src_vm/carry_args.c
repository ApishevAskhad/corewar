/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carry_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 23:38:27 by slindgre          #+#    #+#             */
/*   Updated: 2020/06/04 23:46:02 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	check_reg_number(int reg_num)
{
	if (0 < reg_num && reg_num <= REG_NUMBER)
		return (TRUE);
	return (FALSE);
}

static int	set_carry_arg(t_game *game, t_carry *carry, uint8_t arg_code,
int arg_n)
{
	int	res;
	int pos;

	res = TRUE;
	pos = (MEM_SIZE + carry->pos + carry->jump) % MEM_SIZE;
	if (arg_code == REG_CODE)
	{
		carry->args[arg_n] = game->mem[pos % MEM_SIZE];
		res = check_reg_number(carry->args[arg_n]);
		carry->jump += 1;
	}
	if (arg_code == IND_CODE)
	{
		carry->args[arg_n] = read_2_bytes_from_mem(game, pos);
		carry->jump += IND_SIZE;
	}
	if (arg_code == DIR_CODE)
	{
		carry->args[arg_n] = read_2_bytes_from_mem(game, pos);
		if (game->dir_sizes[carry->op - 1] == DIR_SIZE)
			carry->args[arg_n] = read_4_bytes_from_mem(game, pos);
		carry->jump += game->dir_sizes[carry->op - 1];
	}
	return (res);
}

int			set_carry_args(t_game *game, t_carry *carry)
{
	int		i;
	int32_t	res;
	uint8_t	args_code;
	uint8_t	arg_code;

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
		arg_code = (args_code >> (8 - (i + 1) * 2)) & 3;
		if (set_carry_arg(game, carry, arg_code, i) == FALSE)
			res = FALSE;
		i++;
	}
	return (res);
}
