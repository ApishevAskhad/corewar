/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 01:50:02 by slindgre          #+#    #+#             */
/*   Updated: 2020/06/06 15:25:49 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_lld(t_game *game, t_carry *carry)
{
	int		pos;
	int32_t	res;

	if (carry->arg_types[0] == DIR_CODE)
	{
		res = carry->args[0];
	}
	else
	{
		pos = MEM_SIZE + carry->pos + carry->args[0];
		res = read_2_bytes_from_mem(game, pos);
	}
	carry->r[carry->args[1] - 1] = res;
	carry->carry = (res == 0) ? 1 : 0;
	if (game->v & LOG_OPERATIONS)
	{
		ft_printf("P %4d | lld %d r%d\n",
		carry->id, res, carry->args[1]);
	}
}

void	op_lldi(t_game *game, t_carry *carry)
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
	pos = MEM_SIZE + carry->pos + (arg1 + arg2) % MEM_SIZE;
	carry->r[carry->args[2] - 1] = read_4_bytes_from_mem(game, pos);
	carry->carry = (carry->r[carry->args[2] - 1] == 0) ? 1 : 0;
	if (game->v & LOG_OPERATIONS)
	{
		ft_printf("P %4d | lldi %d %d r%d\n",
		carry->id, arg1, arg2, carry->args[2]);
		ft_printf("       | -> load from %d + %d = %d (with pc %d)\n",
		arg1, arg2, arg1 + arg2, carry->pos + arg1 + arg2);
	}
}

void	op_lfork(t_game *game, t_carry *carry)
{
	t_carry *new;
	int		addr;

	addr = carry->pos + carry->args[0];
	new = new_carry(0, addr);
	new->carry = carry->carry;
	new->live = carry->live;
	ft_memcpy(new->r, carry->r, REG_SIZE * REG_NUMBER);
	new->next = game->carries;
	game->carries = new;
	if (game->v & LOG_OPERATIONS)
	{
		ft_printf("P %4d | lfork %d (%d)\n",
		carry->id, carry->args[0], addr);
	}
}

void	op_aff(t_game *game, t_carry *carry)
{
	int32_t arg1;

	(void)game;
	arg1 = carry->r[carry->args[0] - 1];
	ft_printf("Aff: %c\n", arg1);
}
