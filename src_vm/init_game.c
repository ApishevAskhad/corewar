/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:43:01 by slindgre          #+#    #+#             */
/*   Updated: 2019/11/13 23:09:24 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	init_game(t_game *game)
{
	assert(game != NULL);
	ft_bzero(game, sizeof(game));
	game->dump = OFF;
	game->cycle_to_die = CYCLE_TO_DIE;
}
