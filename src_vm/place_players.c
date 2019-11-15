/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:08:15 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/12 21:44:51 by gloras-t         ###   ########.fr       */
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
