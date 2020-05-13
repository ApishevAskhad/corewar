/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_place_players_code.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:16:56 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/13 20:15:46 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	main()
{
    t_game game;
    t_carry *carry;

	carry = NULL;
    ft_bzero(&game, sizeof(t_game));
    int i = 0;
    game.players_nbr = 3;
    while (i < game.players_nbr)
    {
        ft_memset(game.players[i].code, i * 10 + 200, CHAMP_MAX_SIZE);
        i++;
    }
    place_players_code(&game, &carry);
    print_hexdump(game.mem, MEM_SIZE);
    return (0);
}
