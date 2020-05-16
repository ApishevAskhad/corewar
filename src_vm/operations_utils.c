/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 01:47:56 by slindgre          #+#    #+#             */
/*   Updated: 2020/05/15 08:20:37 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	write_4bytes_to_mem(t_game *game, int pos, int src)
{
	game->mem[pos % MEM_SIZE] = (UC)((src >> (CHAR_BIT * 3)) & 0xff);
	game->mem[(pos + 1) % MEM_SIZE] = (UC)(src >> ((CHAR_BIT * 2)) & 0xff);
	game->mem[(pos + 2) % MEM_SIZE] = (UC)(src >> ((CHAR_BIT * 1)) & 0xff);
	game->mem[(pos + 3) % MEM_SIZE] = (UC)(src & 0xff);
}

int		read_n_bytes_from_mem(t_game *game, int pos, int n)
{
	int	res;
	int	i;
	
	i = 0;
	res = 0;
	while (i < n)
	{
		res |= (int)(game->mem[(pos + i) % MEM_SIZE]) << (CHAR_BIT * (n - i - 1));
		i++;
	}
	return (res);
}

int		read_2_bytes_from_mem(t_game *game, int pos)
{
	int16_t	res;

	res = (int16_t)(game->mem[pos % MEM_SIZE]) << CHAR_BIT;
	res |= (int16_t)(game->mem[(pos + 1) % MEM_SIZE]);
	return (res);
}