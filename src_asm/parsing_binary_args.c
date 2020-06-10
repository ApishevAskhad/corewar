/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_binary_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 09:15:47 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/10 14:26:55 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static size_t	save_bin_arg(unsigned char *bin_data, t_arg *arg)
{
	int			j;

	j = 0;
	while (j < arg->size)
	{
		((unsigned char *)(&arg->value))[arg->size - j - 1] = bin_data[j];
		j++;
	}
	if (arg->size == sizeof(char))
		arg->value = (char)arg->value;
	else if (arg->size == sizeof(short int))
		arg->value = (short int)arg->value;
	arg->str_value = ft_itoa(arg->value);
	return (j);
}

static void		check_bin_arg(t_line *line, int i, size_t pos,
										t_file *file)
{
	char		*message;
	t_arg		arg;

	arg = line->args[i];
	if (!(line->op_data->arg_types[i] & arg.type))
	{
		message = make_type_error_message(line, i, file->filename);
		fill_error(file, NULL, (t_pos)(ssize_t)pos, message);
		file->error_data->is_needed_to_free_message = TRUE;
	}
	else if ((arg.type == T_REG) && ((char)arg.value < 0))
		fill_error(file, NULL, (t_pos)(ssize_t)pos,
					"Registry argument value cannot be negative");
	else if ((arg.type == T_REG) && (arg.value > 99))
		fill_error(file, NULL, (t_pos)(ssize_t)pos,
					"Registry argument value cannot be larger than 99");
	
}

size_t			parse_bin_args(unsigned char *bin_data, t_line *line,
								size_t pos, t_file *file)
{
	int			i;
	size_t		arg_len;
	size_t		bytes_parsed;

	i = 0;
	bytes_parsed = 0;
	arg_len = 0;
	while (i < line->op_data->number_of_args && !(file->error_data))
	{
		if ((pos + bytes_parsed + line->args[i].size) > file->code_size)
			fill_error(file, NULL, (t_pos)(ssize_t)-1,
						"Some operations/arguments are incomplete or missing");
		else
			arg_len = save_bin_arg(bin_data + bytes_parsed,
											&(line->args[i]));
		if (!(file->error_data))
			check_bin_arg(line, i++, pos + bytes_parsed, file);
		bytes_parsed += arg_len;
	}
	return (bytes_parsed);
}
