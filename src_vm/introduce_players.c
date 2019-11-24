/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   introduce_players.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:47:44 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/16 22:05:41 by slindgre         ###   ########.fr       */
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

void	print_dump(UC *ptr, size_t size)
{
	assert(ptr != NULL);
	size_t	i;

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