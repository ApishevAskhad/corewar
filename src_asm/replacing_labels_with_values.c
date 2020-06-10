/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replacing_labels_with_values.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:30:43 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/10 15:37:43 by dtimeon          ###   ########.fr       */
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

static void				replace_label_with_value(t_file *file, t_arg *arg,
													int i, t_line *line)
{
	t_label				*label;
	unsigned char		is_value_set;
	char				*message;
	char				*arg_index;

	label = file->labels;
	is_value_set = FALSE;
	while (label && !is_value_set)
	{
		if (is_label_names_match(label, arg))
		{
			arg->value = label->op_line->pos - line->pos;
			is_value_set = TRUE;
		}
		label = label->next;
	}
	if (!is_value_set)
	{
		arg_index = ft_itoa(i + 1);
		message = ft_strjoin("Couldn't find label to dereference argument #",
								arg_index);
		fill_error(file, line, (t_pos)(arg->pos + 1), message);
		file->error_data->is_needed_to_free_message = TRUE;
		ft_strdel(&arg_index);
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
