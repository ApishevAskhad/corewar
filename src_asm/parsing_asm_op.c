/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_asm_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:40:26 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/28 09:50:12 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** "'Argument #'arg_num' of operation 'name' cannot be of type 'type'"
*/
static char					*make_type_error_message(t_line *line, int i,
														char *filename)
{
	char					*message;
	const char				*type;
	char					*arg_num;
	size_t					message_len;
	size_t					name_len;

	type = ((const char*[3])TYPES_STRINGS)[line->args[i].code - 1];
	name_len = ft_strlen(line->op_data->name);
	arg_num = ft_itoa(i + 1);
	message_len = 47 + 1 + name_len + ft_strlen(type);
	message = ft_strnew(message_len);
	if (!message)
		exit_with_allocation_error(filename);
	ft_strcpy(message, "Argument #");
	ft_strcpy(message + 10, arg_num);
	ft_strcpy(message + 11, " of the operation ");
	ft_strcpy(message + 29, line->op_data->name);
	ft_strcpy(message + 29 + name_len, " cannot be of type ");
	ft_strcpy(message + 48 + name_len, type);
	ft_strdel(&arg_num);
	return(message);
}

unsigned char				is_arg_correct(t_line *line, int i, t_file *file)
{
	char					*message;
	t_arg					arg;

	arg = line->args[i];
	if (!(line->op_data->arg_types[i] & arg.type))
	{
		message = make_type_error_message(line, i, file->filename);
		fill_error(file, line, 0, message);
		file->error_data->is_needed_to_free_message = TRUE;
	}
	else if ((arg.type == T_REG) && arg.has_value_from_label)
		fill_error(file, line, 0, "Registry argument value cannot be a label");
	else if ((arg.type == T_REG) && (arg.value < 0))
		fill_error(file, line, 0, "Registry argument value cannot be negative");
	else if ((arg.type == T_REG) && (arg.value_len > 2))
		fill_error(file, line, 0, "Registry argument value is too long");
	if (!(file->error_data))
		return(TRUE);
	return(FALSE);
}

static void					check_sep_symbol(t_file *file, t_line *line,
												char **str)
{
	*str = find_first_non_space_char(*str);
	if  (!(*str) || (!(**str)))
		fill_error(file, line, ft_strlen(line->initial_str), "Unexpected line "
			"end, there should be a separator symbol and more arguments");
	else if (**str != SEPARATOR_CHAR)
		fill_error(file, line, *str - line->initial_str, 
					"Expected separator symbol before the next argument");
	else
		(*str)++;
}

static unsigned short int	calc_op_size(t_line *line)
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
	return(len);
}

void						parse_asm_op(t_file *file, t_line *cur_line,
											char **start_pos)
{
	int						i;

	cur_line->op_data = get_op(start_pos);
	if (!(cur_line->op_data))
		fill_error(file, cur_line, *start_pos - cur_line->initial_str,
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
				if (!(file->error_data) && is_arg_correct(cur_line, i, file) &&
						(++i < cur_line->op_data->number_of_args))
					check_sep_symbol(file, cur_line, start_pos);
			}
			else
				fill_error(file, cur_line, 0, "Expected more arguments");
		}
		if (!(file->error_data))
			cur_line->len = calc_op_size(cur_line);
	}
}
