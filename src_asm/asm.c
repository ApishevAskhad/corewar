/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 20:55:42 by gloras-t          #+#    #+#             */
/*   Updated: 2020/06/13 22:35:28 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		open_file(char *filename)
{
	int			fd;

	fd = open(filename, O_RDONLY);
	if (is_valid_file(fd, filename))
		return (fd);
	return (-1);
}

static int		process_file(char *filename, short int options)
{
	int			fd;
	t_file		*file;
	int			status;

	fd = open_file(filename);
	if (fd >= 0)
	{
		file = read_file(fd, filename);
		if (file->is_read_successfully)
		{
			parse_file(file);
			if (file->is_correct)
				translate_file(file, options);
			else
				print_file_parsing_error(file);
		}
		status = (file->is_correct) ? 0 : 1;
		delete_file(&file);
		close(fd);
	}
	else
		status = 1;
	return (status);
}

int				main(int argc, char *argv[])
{
	int			i;
	int			args_read;
	short int	options;
	int			status;

	i = 1;
	status = 0;
	if (argc > 1)
	{
		args_read = read_options(argv + 1, argc - 1, &options);
		if (options)
			i += args_read;
		if (argc == i)
		{
			print_error(NULL, "No files. Specify filename after options");
			status = 1;
		}
		while (i < argc)
			status |= process_file(argv[i++], options);
	}
	else
		print_usage(argv[0]);
	return (status);
}
