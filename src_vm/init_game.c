/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:43:01 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/16 22:50:27 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_game(t_game *game)
{
	assert(game != NULL);
	ft_bzero(game, sizeof(t_game));
	game->dump = OFF;
	game->cycle_to_die = CYCLE_TO_DIE;
}
