/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anna <anna@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:08:08 by dtimeon           #+#    #+#             */
/*   Updated: 2019/11/15 18:08:25 by anna             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_usage(char *program_path)
{
	ft_printf("Usage: %s [-a] [source.s binary.cor ... ]\n", program_path);
	ft_printf("\t-a : Instead of creating a .cor/.s file, outputs a stripped ");
	ft_printf("and annotated version of the code to the standard output\n");
}
