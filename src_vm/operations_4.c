/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 01:50:02 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/17 03:06:15 by slindgre         ###   ########.fr       */
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
		pos = MEM_SIZE + carry->pos + carry->args[0];
		res = read_n_bytes_from_mem(game, pos, REG_SIZE);
	}
	carry->r[carry->args[1] - 1] = res;
	carry->carry = 0;
	if (res == 0)
		carry->carry = 1;
	if (game->v)
	{
		ft_printf("P %4d | lld %d r%d\n",
		carry->id, res, carry->args[1]);
	}
}

void	op_lldi(t_game *game, t_carry *carry)
{
	int	pos;
	int	res;
	int	arg1;
	int	arg2;

	arg1 = carry->args[0];
	arg2 = carry->args[1];
	if (carry->arg_types[0] == T_REG)
		arg1 = carry->r[carry->args[0] - 1];
	if (carry->arg_types[1] == T_REG)
		arg2 = carry->r[carry->args[1] - 1];
	if (carry->arg_types[0] == T_IND)
	{
		pos = MEM_SIZE + carry->pos + (carry->args[0] % IDX_MOD);
		arg1 = read_n_bytes_from_mem(game, pos, REG_SIZE);
	}
	pos = MEM_SIZE + carry->pos + arg1 + arg2;
	res = read_n_bytes_from_mem(game, pos, REG_SIZE);
	carry->r[carry->args[2] - 1] = res;
	carry->carry = 0;
	if (res == 0)
		carry->carry = 1;
	if (game->v)
	{
		ft_printf("P %4d | lldi %d %d r%d\n",
		carry->id, arg1, arg2, carry->args[2]);
		ft_printf("       | load from %d + %d = %d (with pc %d)\n",
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
	if (game->v)
	{
		ft_printf("P %4d | lfork %d (%d)\n",
		carry->id, carry->args[0], addr);
	}
}

void	op_aff(t_game *game, t_carry *carry)
{
	int	arg1;

	if (game->aff == TRUE)
	{
		arg1 = carry->r[carry->args[0] - 1];
		ft_printf("%c", (char)arg1);
	}
}
