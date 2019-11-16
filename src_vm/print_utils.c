/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:48:39 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/16 22:06:36 by slindgre         ###   ########.fr       */
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
	exit(ERR_USAGE);
}

void	print_error(int error, char *name)
{
	char *error_msg[] = {
    	"Success",
		"Usage",
		"file extension is not .cor:",
    	"can't read source file",
		"not enough data in file",
		"champion's execution code is too large",
		"code size doesn't fit with actual exec code size in",
		"no magic header in",
		"no first gap in",
		"no second gap in",
		"Player number bigger than MAX_PLAYERS:",
		"Player number should be real, got:",
		"Player with this number already exists, got:",
		"Player numbers are not consistent, lost: ",
		"Dump"
	};

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

void	print_catty_list(t_carry *head)
{
	while (head)
	{
		ft_printf("carry number: %d\n", head->nbr);
		head = head->next;
	}
}
