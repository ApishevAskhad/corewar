/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:08:15 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/04 18:46:46 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    place_players_code(t_game *game)
{
    assert(game != NULL);
    int i;
    int n;
    UC  *start;

    i = 0;
    n = game->players_nbr;
    while (i < n)
    {
        start = game->mem + i * MEM_SIZE / n;
        ft_memcpy(start, game->players[i].code, CHAMP_MAX_SIZE);
        i++;
    }
}