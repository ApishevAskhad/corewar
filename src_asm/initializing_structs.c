/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing_structs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:45:59 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/10 17:26:24 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_line				*init_line(void)
{
	t_line			*line;

	line = (t_line *)ft_memalloc(sizeof(t_line));
	return (line);
}

t_label				*init_label(char *label_name, char *filename)
{
	t_label			*label;

	label = (t_label *)ft_memalloc(sizeof(t_label));
	if (!label)
		exit_with_allocation_error(filename);
	label->name = label_name;
	label->name_len = ft_strlen(label_name);
	return (label);
}

t_warning			*init_warning(char *filename)
{
	t_warning		*warning;

	warning = (t_warning *)ft_memalloc(sizeof(t_warning));
	if (!warning)
		exit_with_allocation_error(filename);
	return (warning);
}

t_error_data		*init_error_data(char *filename)
{
	t_error_data	*error_data;

	error_data = (t_error_data *)ft_memalloc(sizeof(t_error_data));
	if (!error_data)
		exit_with_allocation_error(filename);
	return (error_data);
}

t_file				*init_file(int fd, char *filename)
{
	t_file			*file;
	t_line			*line;

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
