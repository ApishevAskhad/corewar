/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 03:09:25 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/19 01:46:48 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	write_4_bytes_to_mem(t_game *game, int pos, int src)
{
	pos = MEM_SIZE + pos;
	game->mem[pos % MEM_SIZE] = (UC)((src >> (8 * 3)) & 0xff);
	game->mem[(pos + 1) % MEM_SIZE] = (UC)(src >> ((8 * 2)) & 0xff);
	game->mem[(pos + 2) % MEM_SIZE] = (UC)(src >> ((8 * 1)) & 0xff);
	game->mem[(pos + 3) % MEM_SIZE] = (UC)(src & 0xff);
}

int		read_4_bytes_from_mem(t_game *game, int pos)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (i < 4)
	{
		res |= (int)(game->mem[(pos + i) % MEM_SIZE]) <<
		(8 * (4 - i - 1));
		i++;
	}
	return (res);
}

int		read_2_bytes_from_mem(t_game *game, int pos)
{
	int16_t	res;

	res = (int16_t)(game->mem[pos % MEM_SIZE]) << 8;
	res |= (int16_t)(game->mem[(pos + 1) % MEM_SIZE]);
	return (res);
}
