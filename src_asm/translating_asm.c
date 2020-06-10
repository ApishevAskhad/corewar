/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translating_asm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 09:43:34 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/10 09:48:30 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		translate_asm_args(t_line *line, void **dest)
{
	int			i;
	size_t		value;

	i = 0;
	while (i < line->op_data->number_of_args)
	{
		value = to_big_endian(line->args[i].value, line->args[i].size);
		ft_memcpy(*dest, (void *)&value, line->args[i].size);
		*dest += line->args[i].size;
		i++;
	}
}

static void		translate_asm_code(t_file *file)
{
	void		*dest;
	size_t		data;
	t_line		*cur_line;

	file->champ_code = (unsigned char *)ft_memalloc(sizeof(unsigned char) *
													file->code_size);
	dest = file->champ_code;
	cur_line = file->first_code_line;
	while (cur_line != file->last_line)
	{
		if (cur_line->op_data)
		{
			data = to_big_endian(cur_line->op_data->op_code, OP_SIZE);
			ft_memcpy(dest, (void *)&data, OP_SIZE);
			dest += OP_SIZE;
			if (cur_line->op_data->has_arg_type_code)
			{
				data = to_big_endian(cur_line->arg_types_code, TYPES_SIZE);
				ft_memcpy(dest, (void *)&data, TYPES_SIZE);
				dest += TYPES_SIZE;
			}
			translate_asm_args(cur_line, &dest);
		}
		cur_line = cur_line->next;
	}
}

static void		translate_asm_header(t_file *file)
{
	size_t		data;
	void		*dest;

	file->header_size = sizeof(t_magic) + PROG_NAME_LENGTH + COMMENT_LENGTH +
					2 * sizeof(t_sep) + sizeof(t_prog_size);
	data = to_big_endian(COREWAR_EXEC_MAGIC, sizeof(t_magic));
	file->header = (unsigned char *)ft_memalloc(sizeof(unsigned char) *
												file->header_size);
	dest = (void *)file->header;
	ft_memcpy(dest, (void *)&data, sizeof(t_magic));
	dest += sizeof(t_magic);
	ft_memcpy(dest, (void *)file->champ_name, ft_strlen(file->champ_name));
	dest += PROG_NAME_LENGTH;
	ft_memcpy(dest, (t_sep)0, sizeof(t_sep));
	dest += sizeof(t_sep);
	data = to_big_endian(file->code_size, sizeof(t_prog_size));
	ft_memcpy(dest, (void *)&data, sizeof(t_prog_size));
	dest += sizeof(t_prog_size);
	ft_memcpy(dest, (void *)file->champ_comment,
				ft_strlen(file->champ_comment));
	dest += COMMENT_LENGTH;
	ft_memcpy(dest, 0, sizeof(t_sep));
}

void			translate_asm(t_file *file, short int options)
{
	(void)options;
	translate_asm_header(file);
	translate_asm_code(file);
}
