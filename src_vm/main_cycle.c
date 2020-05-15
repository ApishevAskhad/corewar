/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/17 19:52:39 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/15 02:42:02 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	execute_carry(t_game *game, t_carry *carry)
{
	t_handler	func;

	func = (t_handler)game->operations[carry->op - 1];
	func(game, carry);
}

void	execute_carries(t_game *game, t_carry *carry)
{
	while (carry)
	{
		if (carry->timer == 0)
		{
			carry->op = game->mem[carry->pos];
			if (check_op_code(game->mem[carry->pos]))
				carry->timer = game->timers[carry->op - 1];
		}
		if (carry->timer > 0)
			carry->timer -= 1;
		if (carry->timer == 0)
		{
			if (check_op_code(carry->op))
			{
				if (set_carry_args(game, carry) &&
				check_args_code(carry, carry->op,
				game->mem[(carry->pos + 1) % MEM_SIZE]))
					execute_carry(game, carry);
				carry->pos = (carry->pos + carry->jump) % MEM_SIZE;
			}
			else
				carry->pos += 1;
		}
		carry = carry->next;
	}
}

void	check_lives(t_game *game, t_carry **carry)
{
	t_carry *head;
	t_carry *temp;

	head = *carry;
	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->live)
		{
			game->lives += 1;
			temp->live = 0;
		}
		else
			*carry = del_carry(*carry, temp);
	}
}

void	main_cycle(t_game *game)
{
	assert(game != NULL);
	assert(game->carries != NULL);
	game->alive = game->players_nbr;
	while (game->carries)
	{
		game->cycles += 1;
		execute_carries(game, game->carries);
		if (game->cycle_to_die <= 0 || game->cycles % game->cycle_to_die == 0)
		{
			game->checkin_nbr += 1;
			check_lives(game, &(game->carries));
			if (game->lives >= NBR_LIVE || game->checkin_nbr == MAX_CHECKS)
			{
				game->cycle_to_die -= CYCLE_DELTA;
				game->checkin_nbr = 0;
			}
			game->lives = 0;
		}
		if (game->cycles == game->dump)
			print_dump(game->mem, MEM_SIZE);
	}
}
