/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:08:15 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/15 00:23:13 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	place_players_code(t_game *game, t_carry **carry)
{
	int				i;
	int				n;
	unsigned char	*start;

	assert(game != NULL);
	i = 0;
	n = game->players_nbr;
	while (i < n)
	{
		start = game->mem + i * MEM_SIZE / n;
		ft_memcpy(start, game->players[i].code, CHAMP_MAX_SIZE);
		push_carry(carry, -i - 1, i * MEM_SIZE / n);
		i++;
	}
}
