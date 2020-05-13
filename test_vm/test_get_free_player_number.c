/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_get_free_player_number.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 21:13:34 by gloras-t          #+#    #+#             */
/*   Updated: 2020/05/13 20:33:43 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	main()
{
	t_player	players[MAX_PLAYERS];

	ft_bzero(players, sizeof(players));
	assert(get_free_player_number(players) == 1);
	
	players[0].magic = COREWAR_EXEC_MAGIC;	
	assert(get_free_player_number(players) == 2);
	
	ft_bzero(players, sizeof(players));
	players[1].magic = COREWAR_EXEC_MAGIC;
	assert(get_free_player_number(players) == 1);

	ft_bzero(players, sizeof(players));
	players[0].magic = COREWAR_EXEC_MAGIC;
	players[2].magic = COREWAR_EXEC_MAGIC;
	assert(get_free_player_number(players) == 2);

	players[1].magic = COREWAR_EXEC_MAGIC;
	assert(get_free_player_number(players) == 4);

	players[3].magic = COREWAR_EXEC_MAGIC;
	assert(get_free_player_number(players) == 5);
	
	ft_printf("{green}OK{eoc} {yellow}get_free_player_number(t_player players[MAX_PLAYERS]);{eoc}\n");
	return (0);
}
