/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_reading.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:45:26 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/11 02:10:18 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void				read_asm_file(t_file *file)
{
	char				*buffer;
	t_line				*temp_line;

	while ((get_next_line(file->fd, &buffer) > 0))
	{
		if (is_not_blank_str(buffer) && is_not_comment(buffer))
		{
			file->last_line->initial_str = buffer;
			temp_line = init_line();
			file->last_line->next = temp_line;
			file->last_line = temp_line;
		}
		else
			file->last_line->initial_str = buffer;
	}
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
