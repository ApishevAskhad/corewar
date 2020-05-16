/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:45:26 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/16 05:20:50 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static	void			save_new_line(t_line *line, char *buffer, int line_num)
{
	if (line->initial_str)
		ft_strdel(&(line->initial_str));
	line->num = line_num;
	line->initial_str = buffer;
}

static void				add_new_line(t_file *file)
{
	t_line				*temp_line;

	temp_line = init_line();
	if (!temp_line)
		exit_with_allocation_error(file->filename);
	file->last_line->next = temp_line;
	file->last_line = temp_line;
}

static void				read_asm_file(t_file *file)
{
	char				*buffer;
	unsigned int		line_num;
	int					read_status;

	line_num = 1;
	while ((read_status = get_next_line(file->fd, &buffer)) > 0)
	{
		save_new_line(file->last_line, buffer, line_num++);
		if (is_not_blank_str(buffer) && is_not_comment(buffer))
			add_new_line(file);
	}
	if (line_num > 2 && read_status == 0)
		file->is_read_successfully = 1;
}

static void					read_binary_file(t_file *file)
{
	// TODO: reads and saves binary code segment by segment
	(void)file;
}

t_file					*read_file(int fd, char *filename)
{
	t_file				*file;

	file = init_file(fd, filename);
	if (file->is_assembly)
		read_asm_file(file);
	else
		read_binary_file(file);
	return (file);
}
