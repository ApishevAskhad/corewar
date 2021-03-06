/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealing_with_parsing_errors.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 00:56:31 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/16 12:48:39 by student          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** "'Argument #'arg_num' of operation 'name' cannot be of type 'type'"
*/

char			*make_type_error_message(t_line *line, int i, char *filename)
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
	return (message);
}

void			fill_error(t_file *file, t_line *line,
								t_pos pos, char *message)
{
	file->error_data = init_error_data(file->filename);
	file->error_data->line = line;
	file->error_data->message = message;
	if (file->is_assembly)
		file->error_data->asm_pos = pos.asm_pos;
	else
		file->error_data->bin_pos = pos.bin_pos;
}

void			fill_warning(t_file *file, t_line *line, t_pos pos,
								char *message)
{
	t_warning	*new_warning;

	new_warning = init_warning(file->filename);
	new_warning->line = line;
	new_warning->message = message;
	if (file->is_assembly)
		new_warning->asm_pos = pos.asm_pos;
	else
		new_warning->bin_pos = pos.bin_pos;
	if (!(file->first_warning))
	{
		file->first_warning = new_warning;
		file->last_warning = new_warning;
	}
	else
	{
		file->last_warning->next = new_warning;
		file->last_warning = new_warning;
	}
}
