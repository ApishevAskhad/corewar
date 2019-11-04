/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:20:58 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/04 19:50:21 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	not NULL safety
*/
int		is_cor_extension(char *file_name)
{
	assert(file_name != NULL);
	size_t	length;

	length = ft_strlen(file_name);
	if (length >= 4)
		return (!ft_strcmp(COR_EXTENSION, file_name + length - 4));
	return (0);
}

/*
**	not NULL safety
*/
int		has_header(char *byte)
{
	assert(byte != NULL);
	if (((COREWAR_EXEC_MAGIC & 0xFF000000) >> 24) == ((UI)byte[0] & 0xFF)
	&& ((COREWAR_EXEC_MAGIC & 0xFF0000) >> 16) == ((UI)byte[1] & 0xFF)
	&& ((COREWAR_EXEC_MAGIC & 0xFF00) >> 8) == ((UI)byte[2] & 0xFF)
	&& (COREWAR_EXEC_MAGIC & 0xFF) == ((UI)byte[3] & 0xFF))
		return (1);
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