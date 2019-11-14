/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_place_players_code.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:16:56 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/13 23:17:13 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	main()
{
    t_game game;
    int i = 0;

    ft_bzero(&game, sizeof(game));
    game.players_nbr = 3;
    while (i < game.players_nbr)
    {
        ft_memset(game.players[i].code, i * 10 + 200, CHAMP_MAX_SIZE);
        i++;
    }
    place_players_code(&game);
    print_hexdump(game.mem, MEM_SIZE);
    return (0);
}
