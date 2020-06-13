/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacing_labels_with_values.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:30:43 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/12 05:26:01 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned char	is_label_names_match(t_label *label, t_arg *arg)
{
	if (ft_strnequ(label->name, arg->label_name, label->name_len) &&
			(label->name_len == arg->label_name_len))
		return (TRUE);
	return (FALSE);
}

/*
** "Label name '[name]' is used [uses_num] times, the first occurance will be 
** used to dereference argument"
*/
char					*make_multiple_labels_message(t_file *file,
													t_arg *arg,
													int times_label_found)
{
	char				*str_times;
	size_t				str_times_len;
	char				*message;
	char				*temp_str;

	str_times = ft_itoa(times_label_found);
	str_times_len = ft_strlen(str_times);
	message = ft_strnew(7 + arg->label_name_len + 10 + str_times_len + 64);
	if (!message)
		exit_with_allocation_error(file->filename);
	temp_str = message;
	ft_strcpy(temp_str, "Label '");
	temp_str += 7;
	ft_strncpy(temp_str, arg->label_name, arg->label_name_len);
	temp_str += arg->label_name_len;
	ft_strcpy(temp_str, "' is used ");
	temp_str += 10;
	ft_strcpy(temp_str, str_times);
	temp_str += str_times_len;
	ft_strcpy(temp_str, " times, the first occurance will be used to "
						"dereference argument");
	ft_strdel(&str_times);
	return (message);
}

void					make_no_label_error(t_file *file, t_line *line,
											t_arg *arg, int i)
{
	char				*message;
	char				*arg_index;

	arg_index = ft_itoa(i + 1);
	message = ft_strjoin("Couldn't find label to dereference argument #",
							arg_index);
	fill_error(file, line, (t_pos)(arg->pos), message);
	file->error_data->is_needed_to_free_message = TRUE;
	ft_strdel(&arg_index);
}

static void				replace_label_with_value(t_file *file, t_arg *arg,
													int i, t_line *line)
{
	t_label				*label;
	int					times_label_found;
	char				*message;

	label = file->labels;
	times_label_found = 0;
	while (label)
	{
		if (is_label_names_match(label, arg))
		{
			if (times_label_found == 0)
				arg->value = label->op_line->pos - line->pos;
			times_label_found++;
		}
		label = label->next;
	}
	if (times_label_found == 0)
		make_no_label_error(file, line, arg, i);
	else if (times_label_found > 1)
	{
		message = make_multiple_labels_message(file, arg, times_label_found);
		fill_warning(file, line, (t_pos)arg->pos, message);
		file->last_warning->is_needed_to_free_message = TRUE;
	}
}

void				replace_label_args(t_file *file)
{
	t_line			*cur_line;
	int				i;

	cur_line = file->first_code_line;
	while (cur_line != file->last_line && !(file->error_data))
	{
		if (cur_line->has_label_to_find)
		{
			i = 0;
			while (i < cur_line->op_data->number_of_args && !(file->error_data))
			{
				if (cur_line->args[i].has_value_from_label)
					replace_label_with_value(file, &(cur_line->args[i]), i,
												cur_line);
				i++;
			}
		}
		cur_line = cur_line->next;
	}
}
