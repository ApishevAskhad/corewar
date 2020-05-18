/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 19:52:39 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/19 02:06:50 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	execute_carry(t_game *game, t_carry *carry)
{
	t_handler	func;

	func = (t_handler)game->operations[carry->op - 1];
	func(game, carry);
}

static void	execute_carries(t_game *game, t_carry *carry)
{
	while (carry)
	{
		if (carry->timer == 0)
		{
			carry->op = game->mem[carry->pos % MEM_SIZE];
			if (check_op_code(game->mem[carry->pos % MEM_SIZE]))
				carry->timer = game->timers[carry->op - 1];
		}
		carry->timer += (carry->timer > 0) ? -1 : 0;
		if (carry->timer == 0)
		{
			if (check_op_code(carry->op))
			{
				if (set_carry_args(game, carry) &&
				check_args_code(carry, carry->op,
				game->mem[(carry->pos + 1) % MEM_SIZE]))
					execute_carry(game, carry);
				print_verbose_movements(game, carry);
			}
			else
				carry->jump = 1;
			carry->pos = (MEM_SIZE + carry->pos + carry->jump) % MEM_SIZE;
		}
		carry = carry->next;
	}
}

static void	check_lives(t_game *game)
{
	t_carry *head;
	t_carry *temp;

	head = game->carries;
	while (head)
	{
		temp = head;
		head = head->next;
		if (game->cycles - temp->live >= game->cycles_to_die ||
		game->cycles_to_die <= 0)
		{
			print_verbose_death(game, temp);
			del_carry(&(game->carries), temp);
		}
	}
}

void		main_cycle(t_game *game)
{
	while (game->carries)
	{
		game->cycles += 1;
		game->cycles_since_last_check += 1;
		print_verbose_cycle(game);
		execute_carries(game, game->carries);
		if (game->cycles_to_die <= 0 || game->cycles_since_last_check ==
		game->cycles_to_die)
		{
			game->checkin_nbr += 1;
			check_lives(game);
			if (game->lives >= NBR_LIVE || game->checkin_nbr == MAX_CHECKS)
			{
				game->cycles_to_die -= CYCLE_DELTA;
				print_verbose_cycles_to_die(game);
				game->checkin_nbr = 0;
			}
			game->lives = 0;
			game->cycles_since_last_check = 0;
		}
		if (game->cycles == game->d)
			print_dump_64(game->mem, MEM_SIZE);
		if (game->cycles == game->dump)
			print_dump_32(game->mem, MEM_SIZE);
	}
}
