/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_asm_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:40:26 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/11 13:41:05 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned char		is_arg_correct(t_line *line, int i, t_file *file)
{
	char					*message;
	t_arg					arg;

	arg = line->args[i];
	if (!(line->op_data->arg_types[i] & arg.type))
	{
		message = make_type_error_message(line, i, file->filename);
		fill_error(file, line, (t_pos)line->args[i].pos, message);
		file->error_data->is_needed_to_free_message = TRUE;
	}
	else if ((arg.type == T_REG) && arg.has_value_from_label)
		fill_error(file, line, (t_pos)(line->args[i].pos + 1),
					"Registry argument value cannot be a label");
	else if ((arg.type == T_REG) && (arg.value < 0))
		fill_error(file, line, (t_pos)(line->args[i].pos + 1),
					"Registry argument value cannot be negative");
	else if ((arg.type == T_REG) && (arg.value_len > 2))
		fill_error(file, line, (t_pos)(line->args[i].pos + 1),
					"Registry argument value is too long");
	if (!(file->error_data))
		return (TRUE);
	return (FALSE);
}

static void					check_sep_symbol(t_file *file, t_line *line,
												char **str)
{
	*str = find_first_non_space_char(*str);
	if (!(*str) || (!(**str)))
		fill_error(file, line, (t_pos)NULL,
					"Unexpected line end, there should be a separator symbol "
					"and more arguments");
	else if (**str != SEPARATOR_CHAR)
		fill_error(file, line, (t_pos)*str,
					"Expected separator symbol before the next argument");
	else
		(*str)++;
}

unsigned short int			calc_op_size(t_line *line)
{
	unsigned short int		len;
	int						i;

	len = 1;
	len += (line->op_data->has_arg_type_code ? 1 : 0);
	i = 0;
	while (i < line->op_data->number_of_args)
	{
		len += line->args[i].size;
		i++;
	}
	return (len);
}

static unsigned char		is_more_args_expected(t_file *file, t_line *line,
													int i)
{
	return (!(file->error_data) && is_arg_correct(line, i, file) &&
						(i + 1 < line->op_data->number_of_args));
}

void						parse_asm_op(t_file *file, t_line *cur_line,
											char **start_pos)
{
	int						i;

	save_op_data(start_pos, cur_line);
	if (!(cur_line->op_data))
		fill_error(file, cur_line, (t_pos)(*start_pos + 1),
					"This is not valid label or valid operation, nor comment");
	else
	{
		i = 0;
		while ((i < cur_line->op_data->number_of_args) && !(file->error_data))
		{
			*start_pos = find_first_non_space_char(*start_pos);
			if (*start_pos)
			{
				parse_asm_arg(start_pos, cur_line, i, file);
				if (is_more_args_expected(file, cur_line, i++))
					check_sep_symbol(file, cur_line, start_pos);
			}
			else
				fill_error(file, cur_line, (t_pos)NULL,
							"Expected more arguments");
		}
		if (!(file->error_data))
			cur_line->len = calc_op_size(cur_line);
	}
}
