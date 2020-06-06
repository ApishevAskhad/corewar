/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_printing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/19 00:44:30 by slindgre          #+#    #+#             */
/*   Updated: 2020/06/04 23:27:43 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_verbose_movements(t_game *game, t_carry *carry)
{
	int	to;
	int	i;

	to = (MEM_SIZE + carry->pos + carry->jump) % MEM_SIZE;
	if ((game->v & LOG_MOVEMENTS) && carry->jump != 0)
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x) ", carry->jump, carry->pos,
		carry->pos + carry->jump);
		i = 0;
		while (i < carry->jump)
		{
			to = (MEM_SIZE + carry->pos + i) % MEM_SIZE;
			ft_printf("%02x ", (int)game->mem[to]);
			i++;
		}
		ft_printf("\n");
	}
}

void	print_verbose_cycle(t_game *game)
{
	if (game->v & LOG_CYCLES)
	{
		ft_printf("It is now cycle %d\n", game->cycles);
	}
}

void	print_verbose_cycles_to_die(t_game *game)
{
	if (game->v & LOG_CYCLES)
	{
		ft_printf("Cycle to die is now %d\n", game->cycles_to_die);
	}
}

void	print_verbose_death(t_game *game, t_carry *carry)
{
	if (game->v & LOG_DEATHS)
	{
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
		carry->id, game->cycles - carry->live, game->cycles_to_die);
	}
}
