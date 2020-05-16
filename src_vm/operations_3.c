/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 01:50:15 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/16 02:35:36 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	op_zjmp(t_game *game, t_carry *carry)
{
	if (carry->carry == 1 && game != NULL)
	{
		carry->pos = (MEM_SIZE + carry->pos + (carry->args[0] % IDX_MOD)) % MEM_SIZE;
		carry->jump = 0;
	}
}

void	op_ldi(t_game *game, t_carry *carry)
{
	int	arg1;
	int	arg2;
	int	pos;

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
	pos = MEM_SIZE + carry->pos + ((arg1 + arg2) % IDX_MOD);
	carry->r[carry->args[2] - 1] = read_n_bytes_from_mem(game, pos, REG_SIZE);
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
	if (carry->arg_types[1] == T_REG)
		arg2 = carry->r[carry->args[1] - 1];
	if (carry->arg_types[2] == T_REG)
		arg3 = carry->r[carry->args[2] - 1];
	if (carry->arg_types[1] == T_IND)
	{
		pos = MEM_SIZE + carry->pos + (carry->args[1] % IDX_MOD);
		arg2 = read_n_bytes_from_mem(game, pos, REG_SIZE);
	}
	pos = MEM_SIZE + carry->pos + ((arg2 + arg3) % IDX_MOD);
	write_4bytes_to_mem(game, pos, arg1);
}

void	op_fork(t_game *game, t_carry *carry)
{
	t_carry *new;

	new = new_carry(0, MEM_SIZE + carry->pos + (carry->args[0] % IDX_MOD));
	new->carry = carry->carry;
	new->live = carry->live;
	ft_memcpy(new->r, carry->r, REG_SIZE * REG_NUMBER);
	new->next = game->carries;
	game->carries = new;
}
