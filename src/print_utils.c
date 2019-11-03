/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slindgre <slindgre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 14:48:39 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/03 18:10:47 by slindgre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_usage(void)
{
	ft_printf("Usage: .corewar [-dump nbr_cycles] [-v]  [[-n number] champion1.cor] ...\n");
    ft_printf("-dump nbr_cycles     : Dumps memory after nbr_cycles cycles then exits\n");
	ft_printf("-v      				: Visual mode\n");
	ft_printf("-n					: sets the number of the next player\n");
}

void	print_error(char *error_msg)
{
	ft_printf("{red}error:{eoc} %s\n", error_msg);
}

void	print_bits_ui(UI number)
{
	size_t	size;

	size = 8 * sizeof(UI);
	while (size--)
	{
		ft_printf("%c", (number & 1) ? '1' : '0');
		number >>= 1;
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
		ft_printf("%c", (number & 1) ? '1' : '0');
		number >>= 1;
	}
}
