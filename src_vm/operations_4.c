/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 01:50:02 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/15 03:36:32 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_lld(t_game *game, t_carry *carry)
{
	int	pos;
	int	res;

	if (carry->arg_types[0] == T_DIR)
	{
		res = carry->args[0];
	}
	else
	{
		pos = carry->pos + carry->args[0];
		res = read_n_bytes_from_mem(game, pos, REG_SIZE);
	}
	carry->r[carry->args[1] - 1] = res;
    carry->carry = 0;
	if (res == 0)
		carry->carry = 1;
}

void	op_lldi(t_game *game, t_carry *carry)
{
	int	pos;
	int	res;
    int	arg1;
	int	arg2;

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
	pos = carry->pos + arg1 + arg2;
    res = read_n_bytes_from_mem(game, pos, REG_SIZE);
	carry->r[carry->args[2] - 1] = res;
    carry->carry = 0;
	if (res == 0)
		carry->carry = 1;
}

void	op_lfork(t_game *game, t_carry *carry)
{
	t_carry *new;

	new = new_carry(0, (carry->pos + carry->args[0]) % MEM_SIZE);
	new->carry = carry->carry;
	new->live = carry->live;
	ft_memcpy(new->r, carry->r, REG_SIZE * REG_NUMBER);
	new->next = game->carries;
	game->carries = new;
}

void	op_aff(t_game *game, t_carry *carry)
{
    int arg1;
    
	if (game != NULL)
	{
		arg1 = carry->r[carry->args[0] - 1];
		ft_printf("%C", (char)arg1);
	}
}