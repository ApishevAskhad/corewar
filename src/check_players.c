/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_players.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 19:34:03 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/04 19:47:01 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void    check_players_nbrs(t_game game)
{
    int i;

    i = 0;
    if (!game.players_nbr)
        print_usage();
    while (i < game.players_nbr)
    {
        if (!game.players[i].magic)
            print_error("Player numbers are not consistent, lost: ",
            ft_itoa(i + 1));
        i++;
    }
}