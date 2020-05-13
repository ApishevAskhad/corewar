/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   introduce_players.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: status <status@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:47:44 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/13 05:23:04 by status           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	introduce_players(t_game game)
{
	int			i;
	t_player	p;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < game.players_nbr)
	{
		p = game.players[i];
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
					i + 1, p.prog_size, p.prog_name, p.comment);
		i++;
	}
}

void	introduce_winner(t_game game)
{
	int			i;
	t_player	p;

	assert(game.alive > 0);
	i = game.alive;
	p = game.players[i - 1];
	ft_printf("Contestant %d, \"%s\", has won !\n", i, p.prog_name);
}

void	print_dump(UC *ptr, size_t size)
{
	size_t	i;

	assert(ptr != NULL);
	i = 0;
	while (i < size)
	{
		if (i % 32 == 0)
			ft_printf("0x%04x :", i);
		ft_printf(" %02x", (int)ptr[i]);
		i++;
		if (i % 32 == 0 || i == size)
			ft_printf("\n");
	}
	exit(ERR_DUMP);
}
