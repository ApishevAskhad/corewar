/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:08:08 by dtimeon           #+#    #+#             */
/*   Updated: 2019/11/14 22:31:19 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_usage(char *program_path)
{
	ft_printf("Usage: %s [-a] [sourcefile.s binaryfile.cor ... ]\n\
\t-a : Instead of creating a .cor/.s file, outputs a stripped and annotated \
version of the code to the standard output\n", program_path);
}
