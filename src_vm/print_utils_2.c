/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:48:39 by gloras-t          #+#    #+#             */
/*   Updated: 2020/05/19 02:37:55 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_usage(char *prog)
{
	int	space_left;
	int	space_right;

	space_left = 3;
	space_right = 8;
	ft_printf("Usage: %s [-dump N] [-v] [[-n N] champion1.cor] ...\n", prog);
	ft_printf("%*c -%-*s: ", space_left, ' ', space_right, "n N");
	ft_printf("Sets the N number of the next player\n");
	ft_printf("%*c -%-*s: ", space_left, ' ', space_right, "a");
	ft_printf("Prints output from \"aff\" (Default is to hide it)\n");
	ft_printf("#### TEXT OUTPUT MODE ####\n");
	ft_printf("%*c -%-*s: ", space_left, ' ', space_right, "dump N");
	ft_printf("Dumps memory after N cycles then exits. 32 bits/line\n");
	ft_printf("%*c -%-*s: ", space_left, ' ', space_right, "d N");
	ft_printf("Dumps memory after N cycles then exits. 64 bits/line\n");
	ft_printf("%*c -%-*s: ", space_left, ' ', space_right, "v N");
	ft_printf("Verbosity levels, can be added together to enable several\n");
	ft_printf("%*c %2s - Show lives\n", space_left * 5, ' ', "1");
	ft_printf("%*c %2s - Show cycles\n", space_left * 5, ' ', "2");
	ft_printf("%*c %2s - Show operations\n", space_left * 5, ' ', "4");
	ft_printf("%*c %2s - Show deaths\n", space_left * 5, ' ', "8");
	ft_printf("%*c %2s - Show PC movements (Except for jumps)\n",
	space_left * 5, ' ', "16");
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

	carry = game->carries;
	while (carry)
	{
		ft_printf("carry %4d | pos %4d | op %02x\n",
		carry->id, carry->pos, game->mem[carry->pos]);
		carry = carry->next;
	}
}
