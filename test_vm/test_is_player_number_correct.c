/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_player_number_correct.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 21:54:38 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/13 22:27:13 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	main()
{
	t_game	game;

	ft_bzero(&game, sizeof(t_game));
	assert(is_player_number_correct(1, game));
	assert(!is_player_number_correct(5, game));

	game.players[0].magic = COREWAR_EXEC_MAGIC;
	assert(!is_player_number_correct(1, game));
	assert(!is_player_number_correct(-1, game));
	assert(is_player_number_correct(2, game));
	return (0);
}
