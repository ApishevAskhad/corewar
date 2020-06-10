/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translating_bin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 09:43:57 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/10 10:16:08 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		translate_bin_header(t_file *file)
{
	size_t		name_cmd_len;
	size_t		comment_cmd_len;
	size_t		name_len;
	size_t		comment_len;
	char		*dest;

	name_cmd_len = ft_strlen(NAME_CMD_STRING);
	comment_cmd_len = ft_strlen(COMMENT_CMD_STRING);
	name_len = ft_strlen(file->champ_name);
	comment_len = ft_strlen(file->champ_comment);
	file->header_size = name_cmd_len + comment_cmd_len + name_len +
						comment_len + sizeof(char) * 9;
	file->header = (unsigned char *)ft_strnew(file->header_size);
	if (!(file->header))
		exit_with_allocation_error(file->filename);
	dest = (char *)file->header;
	ft_strcpy(dest, NAME_CMD_STRING " " STRING_START);
	dest += name_cmd_len + sizeof(char) * 2;
	ft_strcpy(dest, file->champ_name);
	dest += name_len;
	ft_strcpy(dest, STRING_END "\n" COMMENT_CMD_STRING " " STRING_START);
	dest += comment_cmd_len + sizeof(char) * 4;
	ft_strcpy(dest, file->champ_comment);
	dest += comment_len;
	ft_strcpy(dest, STRING_END "\n\n");
}

static void		translate_bin_args(t_line *line, char **dest)
{
	t_arg		arg;
	int			i;

	i = 0;
	while (i < line->op_data->number_of_args)
	{
		arg = line->args[i];
		**dest = ' ';
		*dest += sizeof(char);
		ft_strcpy(*dest, arg.sym);
		*dest += ft_strlen(arg.sym);
		ft_strcpy(*dest, arg.str_value);
		*dest += ft_strlen(arg.str_value);
		i++;
		if (i < line->op_data->number_of_args)
		{
			**dest = SEPARATOR_CHAR;
			*dest += sizeof(char);
		}
	}
}

/*
** [5 spaces][op][space][sym][value][sep][space][next arg]\n
*/
static void		translate_bin_code(t_file *file)
{
	char		*dest;
	t_line		*cur_line;

	file->code_size = file->str_code_len;
	file->champ_code = (unsigned char *)ft_strnew(file->str_code_len);
	if (!file->champ_code)
		exit_with_allocation_error(file->filename);
	dest = (char *)file->champ_code;
	cur_line = file->first_code_line;
	while (cur_line != file->last_line)
	{
		ft_strcpy(dest, "     ");
		dest += sizeof(char) * 5;
		ft_strcpy(dest, cur_line->op_data->name);
		dest += cur_line->op_data->name_len;
		translate_bin_args(cur_line, &dest);
		*dest = '\n';
		dest += sizeof(char);
		cur_line = cur_line->next;
	}
}

void			translate_bin(t_file *file, short int options)
{
	(void)options;
	ft_memdel((void **)&file->header);
	if (file->champ_code)
		ft_memdel((void **)&file->champ_code);
	translate_bin_header(file);
	translate_bin_code(file);
}
