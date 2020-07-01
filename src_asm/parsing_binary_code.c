/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_binary_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:30:39 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/10 14:26:51 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned char	*parse_bin_arg_types(unsigned char *bin_data,
											t_line *line,
											ssize_t pos,
											t_file *file)
{
	unsigned char		arg_code;
	unsigned char		*types;
	int					i;

	i = 0;
	if (*bin_data & 3)
		fill_error(file, NULL, (t_pos)pos,
					"Expected arguments types byte to end with 2 zero bits");
	if (!(types = (unsigned char *)ft_memalloc(sizeof(unsigned char) * 3)))
		exit_with_allocation_error(file->filename);
	while (i < line->op_data->number_of_args && !(file->error_data))
	{
		arg_code = (*bin_data & (3 << ((3 - i) * 2))) >> ((3 - i) * 2);
		if (arg_code == REG_CODE)
			types[i] = T_REG;
		else if (arg_code == DIR_CODE)
			types[i] = T_DIR;
		else if (arg_code == IND_CODE)
			types[i] = T_IND;
		else
			fill_error(file, NULL, (t_pos)pos,
						"Incorrect arguments types byte");
		i++;
	}
	return (types);
}

static size_t			save_bin_arg_types(unsigned char *bin_data,
											t_line *line,
											size_t pos,
											t_file *file)
{
	unsigned char		*types;
	int					i;

	if (line->op_data->has_arg_type_code)
	{
		types = parse_bin_arg_types(bin_data, line, pos, file);
		line->arg_types_code = *bin_data;
	}
	else
		types = line->op_data->arg_types;
	i = 0;
	if (!(file->error_data))
	{
		while (i < line->op_data->number_of_args)
		{
			assign_arg_as(types[i], &(line->args[i]),
							line->op_data->has_dir_as_ind);
			i++;
		}
	}
	if (line->op_data->has_arg_type_code)
		ft_memdel((void **)&types);
	return (line->op_data->has_arg_type_code);
}

static size_t			parse_bin_op(unsigned char *bin_data, ssize_t pos,
										t_file *file)
{
	extern t_op			g_op_tab[OP_NUM];
	ssize_t				bytes_parsed;
	t_line				*cur_line;

	bytes_parsed = 1;
	cur_line = file->last_line;
	if ((*bin_data > OP_NUM) || (*bin_data == 0))
		fill_error(file, NULL, (t_pos)pos, "Incorrect operation code");
	else if (pos + bytes_parsed >= file->code_size)
		fill_error(file, NULL, (t_pos)(ssize_t)-1,
					"Some operations/arguments are incomplete or missing");
	else
	{
		cur_line->op_data = &(g_op_tab[*bin_data - 1]);
		bytes_parsed += save_bin_arg_types(bin_data + bytes_parsed, cur_line,
							pos + bytes_parsed, file);
		if (!(file->error_data))
			bytes_parsed += parse_bin_args(bin_data + bytes_parsed, cur_line,
											pos + bytes_parsed, file);
	}
	return (bytes_parsed);
}

/*
** [5 spaces][op][space][sym][value][sep][space][next arg]\n
*/

size_t					calc_str_len(t_line *line)
{
	size_t				len;
	t_arg				arg;
	int					i;

	len = sizeof(char) * 5 + line->op_data->name_len + sizeof(char);
	i = 0;
	while (i < line->op_data->number_of_args)
	{
		arg = line->args[i];
		len += ft_strlen(arg.sym) + ft_strlen(arg.str_value);
		i++;
		if (i < line->op_data->number_of_args)
			len += sizeof(char) * 2;
	}
	len += sizeof(char);
	return (len);
}

void					parse_binary_code(t_file *file)
{
	ssize_t				bytes_parsed;

	bytes_parsed = 0;
	file->first_code_line = file->first_line;
	while ((bytes_parsed < (ssize_t)file->code_size) && !(file->error_data))
	{
		bytes_parsed += parse_bin_op(file->champ_code + bytes_parsed,
										bytes_parsed, file);
		if (!(file->error_data))
		{
			file->last_line->len = calc_op_size(file->last_line);
			file->last_line->pos = bytes_parsed - file->last_line->len;
			file->last_line->str_len = calc_str_len(file->last_line);
			file->str_code_len += file->last_line->str_len;
		}
		if (!(file->error_data) && (bytes_parsed <= file->code_size))
		{
			file->last_line->next = init_line();
			if (!(file->last_line->next))
				exit_with_allocation_error(file->filename);
			file->last_line = file->last_line->next;
		}
	}
}
