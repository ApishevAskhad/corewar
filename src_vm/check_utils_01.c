/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:20:58 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/15 23:03:16 by slindgre         ###   ########.fr       */
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
	if (length >= 4 && !ft_strcmp(COR_EXTENSION, file_name + length - 4))
        return (1);
    print_error(ERR_NO_COR, file_name);
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
            print_error(ERR_PL_NBRS_SEQUENCE, ft_itoa(i + 1));
        i++;
    }
}
