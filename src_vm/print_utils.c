/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:48:39 by gloras-t          #+#    #+#             */
/*   Updated: 2020/05/17 02:59:22 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_usage(void)
{
	int	space_left;
	int	space_right;

	space_left = 3;
	space_right = 8;
	ft_printf("Usage: ./corewar [-dump N] [-v] [[-n N] champion1.cor] ...\n");
	ft_printf("%*c -%-*s: Dumps memory after N cycles then exits\n",
	space_left, ' ', space_right, "dump N");
	ft_printf("%*c -%-*c: Visual mode\n", space_left, ' ', space_right, 'v');
	ft_printf("%*c -%-*s: Sets the N number of the next player\n",
	space_left, ' ', space_right, "n N");
	if (DEBUG == 0)
		exit(ERR_USAGE);
}

void	print_error(int error, char *name)
{
	char *error_msg[15];

	error_msg[0] = "Success";
	error_msg[1] = "Usage";
	error_msg[2] = "file extension is not .cor:";
	error_msg[3] = "can't read source file";
	error_msg[4] = "not enough data in file";
	error_msg[5] = "champion's execution code is too large";
	error_msg[6] = "code size doesn't fit with actual exec code size in";
	error_msg[7] = "no magic header in";
	error_msg[8] = "no first gap in";
	error_msg[9] = "no second gap in";
	error_msg[10] = "Player number bigger than MAX_PLAYERS:";
	error_msg[11] = "Player number should be real, got:";
	error_msg[12] = "Player with this number already exists, got:";
	error_msg[13] = "Player numbers are not consistent, lost: ";
	error_msg[14] = "Dump";
	ft_printf("{red}error:{eoc} %s %s\n", error_msg[error], name);
	if (DEBUG == 0)
		exit(error);
}

void	print_bits_ui(UI number)
{
	size_t	size;

	size = 8 * sizeof(UI);
	while (size--)
	{
		ft_printf("%c", (number & (0x80000000)) ? '1' : '0');
		number <<= 1;
		if (size && !(size % 8))
			ft_printf(" ");
	}
}

void	print_bits_char(char number)
{
	size_t	size;

	size = 8 * sizeof(char);
	while (size--)
	{
		ft_printf("%c", (number & (CHAR_MAX + 1)) ? '1' : '0');
		number <<= 1;
	}
}

void	print_hexdump(UC *ptr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		ft_printf("%02x", (int)ptr[i]);
		i++;
		if (i % 16 == 0 || i == size)
			ft_printf("\n");
		else if (i % 2 == 0)
			ft_printf(" ");
	}
}

void	print_carry_list(t_game *game)
{
	t_carry	*carry;

	ft_printf("here");
	carry = game->carries;
	while (carry)
	{
		ft_printf("carry %4d | pos %4d | op %02x\n",
		carry->id, carry->pos, game->mem[carry->pos]);
		carry = carry->next;
	}
}

void	print_verbose(t_game *game, t_carry *carry)
{
	int	to;
	int	i;

	to = (MEM_SIZE + carry->pos + carry->jump) % MEM_SIZE;
	if (game->v && carry->jump != 0)
	{
		ft_printf("ADV %d (0x%04x -> 0x%04x) ", carry->jump, carry->pos, to);
		i = 0;
		while (i < carry->jump)
		{
			to = (MEM_SIZE + carry->pos + i) % MEM_SIZE;
			ft_printf("%02x ", (int)game->mem[to]);
			i++;
		}
		ft_printf("\n");
	}
}

void	print_verbose_cycle(t_game *game)
{
	if (game->v)
	{
		ft_printf("It is now cycle %d\n", game->cycles);
	}
}

void	print_verbose_cycle_to_die(t_game *game)
{
	if (game->v)
	{
		ft_printf("Cycle to die is now %d\n", game->cycle_to_die);
	}
}

void	print_verbose_death(t_game *game, t_carry *carry)
{
	if (game->v)
	{
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
		carry->id, game->cycles - carry->live, game->cycle_to_die);
	}
}
