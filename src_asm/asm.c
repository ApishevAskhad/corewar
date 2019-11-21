/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:55:42 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/21 22:19:25 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				open_file(char *filename)
{
	int			fd;

	fd = open(filename, O_RDONLY);
	if (is_valid_file(fd, filename))
		return (fd);
	return (-1);
}

void			translate_file(char *filename, short int options)
{
	int			fd;

	fd = open_file(filename);
	if (fd >= 0)
	{
		(void)options;
	}
}

int				main(int argc, char *argv[])
{
	int			i;
	short int	options;

	i = 1;
	if (argc > 1)
	{
		options = read_options(argv[1]);
		if (options)
			i++;
		if (argc == i)
			print_error(NULL, "No files. Specify filename after options");
		while (i < argc)
			translate_file(argv[i++], options);
	}
	else
		print_usage(argv[0]);
	return (0);
}
