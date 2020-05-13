/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing_structs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:45:59 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/11 02:03:18 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_line			*init_line()
{
	t_line		*line;

	line = (t_line *)ft_memalloc(sizeof(t_line));
	return (line);
}

t_file			*init_file(int fd, char *filename)
{
	t_file		*file;
	t_line		*line;

	file = (t_file *)ft_memalloc(sizeof(t_file));
	line = init_line();
	if (!file || !line)
		exit_with_allocation_error(filename);
	file->first_line = line;
	file->last_line = line;
	file->fd = fd;
	file->filename = filename;
	file->is_assembly = ft_strequ(SOURCE_EXTENSION, ft_strrchr(filename, '.'));
	return (file);
}
