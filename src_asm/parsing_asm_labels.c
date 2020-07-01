/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_asm_labels.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:03:54 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/09 10:31:42 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		save_label(t_line *line, t_label *label, size_t code_pos)
{
	line->has_label_in = TRUE;
	line->pos = code_pos;
	line->label = label;
}

static char		*find_next_op_str(t_file *file, t_line **cur_line,
								t_label *first_label, size_t code_pos)
{
	t_label		*temp_label;
	char		*start_pos;
	char		*new_label_name;
	char		*op_pos;

	op_pos = NULL;
	temp_label = first_label;
	while (((*cur_line) != file->last_line) && (!op_pos || is_comment(op_pos)))
	{
		(*cur_line) = (*cur_line)->next;
		skip_non_useful_lines(cur_line);
		if ((*cur_line)->initial_str)
		{
			start_pos = find_first_non_space_char((*cur_line)->initial_str);
			if (*start_pos &&
				(new_label_name = find_label(&start_pos, file, *cur_line)))
			{
				temp_label->next = init_label(new_label_name, file->filename);
				temp_label = temp_label->next;
				save_label(*cur_line, temp_label, code_pos);
			}
			op_pos = find_first_non_space_char(start_pos);
		}
	}
	return (op_pos);
}

static void		save_op_line_to_labels(t_label *first_label)
{
	t_label		*temp_label;

	temp_label = first_label->next;
	while (temp_label)
	{
		temp_label->op_line = first_label->op_line;
		temp_label = temp_label->next;
	}
}

static void		save_labels_to_file(t_label *first_label, t_file *file)
{
	t_label		*temp_label;

	if (file->labels)
	{
		temp_label = file->labels;
		while (temp_label->next)
			temp_label = temp_label->next;
		temp_label->next = first_label;
	}
	else
		file->labels = first_label;
}

void			parse_labels(t_file *file, t_line **cur_line, char **start_pos,
								char *label_name)
{
	t_label		*first_label;
	char		*op_pos;
	t_line		*first_label_line;

	first_label = init_label(label_name, file->filename);
	first_label_line = *cur_line;
	op_pos = find_first_non_space_char(*start_pos);
	if ((!op_pos || is_comment(op_pos)) && (*cur_line)->next != file->last_line)
		op_pos = find_next_op_str(file, cur_line, first_label,
									(*cur_line)->pos);
	*start_pos = op_pos;
	if (op_pos)
		first_label->op_line = *cur_line;
	else
		first_label->op_line = first_label_line;
	if (first_label->next)
		save_op_line_to_labels(first_label);
	save_label(first_label_line, first_label, first_label_line->pos);
	save_labels_to_file(first_label, file);
}
