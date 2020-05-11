/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:55:42 by gloras-t          #+#    #+#             */
/*   Updated: 2020/05/11 19:28:17 by dtimeon          ###   ########.fr       */
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

void			process_file(char *filename, short int options)
{
	int			fd;
	t_file      *file;

	fd = open_file(filename);
	if (fd >= 0)
	{
		file = read_file(fd, filename);
		parse_file(file);
		if (file->is_correct)
			translate_file(file, options);
		else
			print_file_validation_error(file);
	}
	delete_file(&file);
	close(fd);
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
			process_file(argv[i++], options);
	}
	else
		print_usage(argv[0]);
	return (0);
}
