/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 02:46:47 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/10 20:11:56 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	is_valid_extension(char *filename)
{
	char	*dot_pos;

	dot_pos = ft_strrchr(filename, '.');
	if (!dot_pos)
		return (0);
	if (!ft_strequ(dot_pos, SOURCE_EXTENSION) &&
		!ft_strequ(dot_pos, BINARY_EXTENSION))
		return (0);
	return (1);
}

static int	is_readble_file(int fd)
{
	char	*buf;
	int		bytes_read;
	int		lseek_status;

	buf = ft_strnew(1);
	bytes_read = read(fd, buf, O_RDONLY);
	free(buf);
	if (bytes_read < 0)
		return (0);
	lseek_status = lseek(fd, 0, SEEK_SET);
	if (lseek_status < 0)
		return (0);
	return (1);
}

int			is_valid_file(int fd, char *filename)
{
	if (!is_valid_extension(filename))
	{
		print_error(filename, "Filename should have " SOURCE_EXTENSION " or "
					BINARY_EXTENSION " extension");
		return (0);
	}
	if (fd < 0)
	{
		if (!*filename)
			print_error(NULL, "Filename can't be empty");
		else
			print_error(filename, "Unable to open file for reading");
		return (0);
	}
	if (!is_readble_file(fd))
	{
		print_error(filename, "Unable to read file");
		return (0);
	}
	return (1);
}
