/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:20:58 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/14 20:49:56 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	not NULL safety
*/

int	is_cor_extension(char *file_name)
{
	assert(file_name != NULL);
	size_t	length;

	length = ft_strlen(file_name);
	if (length >= 4)
		return (!ft_strcmp(COR_EXTENSION, file_name + length - 4));
	return (0);
}

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
