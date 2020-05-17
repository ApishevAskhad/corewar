/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reading_binary_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 01:21:52 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/17 23:00:50 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static ssize_t		get_champ_code_size(t_file *file, ssize_t header_size)
{
	ssize_t			code_size;

	code_size = lseek(file->fd, 0, SEEK_END) - header_size;
	if (code_size >= 0 &&
		(lseek(file->fd, header_size, SEEK_SET)) >= 0)
		return (code_size);
	else
		return (-1);
}

static void			save_binary_champ_code(t_file *file, ssize_t code_size)
{
	unsigned char	*buffer;
	
	buffer = (unsigned char *)malloc(sizeof(unsigned char) * code_size);
	if (!buffer)
		exit_with_allocation_error(file->filename);
	if (read(file->fd, buffer, code_size) >= 0)
	{
		file->champ_code = buffer;
		file->code_size = code_size;
		file->is_read_successfully = 1;
	}
	else
	{
		ft_memdel((void **)buffer);
		print_error(file->filename, "File reading error");
	}
}

void				read_binary_champ_code(t_file *file, ssize_t header_size)
{
	ssize_t			code_size;

	code_size = get_champ_code_size(file, header_size);
	if (code_size >= 0)
		save_binary_champ_code(file, code_size);
	else
		print_error(file->filename, "Couldn't set file reading position");
}
