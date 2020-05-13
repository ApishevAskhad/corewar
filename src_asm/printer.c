/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:08:08 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/11 02:05:07 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_error(char *filename, char *message)
{
	if (filename)
		ft_printf("Error in file \"%s\": %s\n", filename, message);
	else
		ft_printf("Error: %s\n", message);
}

void			print_file_validation_error(t_file *file)
{
	//TODO: prints nice and clear error message with line num
	// and an arrow pointing to error location
	(void)file;
}

void	print_usage(char *program_path)
{
	ft_printf("Usage: %s [-a] [source.s binary.cor ... ]\n", program_path);
	ft_printf("\t-a : Instead of creating a .cor/.s file, outputs a stripped ");
	ft_printf("and annotated version of the code to the standard output\n");
}
