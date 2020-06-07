/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:08:08 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/07 09:28:49 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		print_error(char *filename, char *message)
{
	if (filename)
		ft_printf("Error in file {blue}%s{eoc}: %s\n", filename, message);
	else
		ft_printf("\t{red}%s{red}\n\n", message);
}

void 		print_bin_parsing_error(t_file *file)
{
	ssize_t	pos;

	pos = file->error_data->error_pos;
	if (pos >= 0)
		ft_printf("     Byte %lli: | {red}%08hhB{eoc} | <-- ", pos,
					*(file->champ_code + pos));
	ft_printf("{red}%s{eoc}\n\n", file->error_data->message);
}

void		print_asm_parsing_error(t_file *file)
{
	size_t	offset;
	size_t	line_num;
	ssize_t	pos;
	char	*message;

	if (file->error_data->line)
	{
		line_num = file->error_data->line->num;
		offset = ft_printf("     line %u: ", line_num);
		offset += count_tabs(file->error_data->line->initial_str) * TAB_LEN;
		pos = file->error_data->error_pos;
		ft_printf("{blue}%s{eoc}\n", file->error_data->line->initial_str);
		ft_printf("{red}% *s{eoc}\n", pos + offset, "^");
	}
	message = file->error_data->message;
	ft_printf("\t{red}%s{eoc}\n\n", message);
}

void		print_file_parsing_error(t_file *file)
{
	ft_printf("Parsing error in file {blue}%s{eoc}:\n", file->filename);
	if (file->is_assembly)
		print_asm_parsing_error(file);
	else
		print_bin_parsing_error(file);
	if (file->error_data->is_needed_to_free_message)
		ft_strdel(&(file->error_data->message));
}

void		print_usage(char *program_path)
{
	ft_printf("Usage: %s [-a] [source.s binary.cor ... ]\n", program_path);
	ft_printf("\t-a : Instead of creating a .cor/.s file, outputs a stripped ");
	ft_printf("and annotated version of the code to the standard output\n");
}
