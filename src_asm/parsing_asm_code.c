/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_asm_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 08:57:24 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/11 14:45:40 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned char	is_line_break_found(t_file *file)
{
	char				last_char;

	if (((lseek(file->fd, -1, SEEK_END)) > 0) &&
		(read(file->fd, &last_char, 1) == 1))
	{
		if (last_char == '\n')
			return (TRUE);
	}
	else
		print_error(file->filename, "File reading failed");
	return (FALSE);
}

static void				process_new_code_line(t_file *file, t_line **cur_line,
												char *end_pos)
{
	if (end_pos && !is_blank_str(end_pos) && !is_comment(end_pos))
		fill_warning(file, *cur_line,
						(t_pos)find_first_non_space_char(end_pos),
						"Unexpected symbol after the oparation");
	(*cur_line)->pos = file->code_size;
	file->code_size += (*cur_line)->len;
	if ((*cur_line)->next == file->last_line)
	{
		if (!is_line_break_found(file))
			fill_error(file, *cur_line, (t_pos)NULL,
				"Every code line should end with a line break symbol");
	}
	if (!(file->error_data))
	{
		*cur_line = (*cur_line)->next;
		skip_non_useful_lines(cur_line);
	}
}

void					parse_asm_code(t_file *file)
{
	t_line				*cur_line;
	char				*start_pos;
	char				*label_name;

	cur_line = file->first_code_line;
	file->code_size = 0;
	while (cur_line != file->last_line && !(file->error_data))
	{
		start_pos = find_first_non_space_char(cur_line->initial_str);
		label_name = find_label(&start_pos, file, cur_line);
		cur_line->pos = file->code_size;
		if (label_name)
			parse_labels(file, &cur_line, &start_pos, label_name);
		if (!(file->error_data) && start_pos)
			parse_asm_op(file, cur_line, &start_pos);
		if (!(file->error_data) &&
				(cur_line->op_data || cur_line->has_label_in))
			process_new_code_line(file, &cur_line, start_pos);
	}
	if (!(file->error_data) && file->labels)
		replace_label_args(file);
}
