/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:08:08 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/13 13:58:19 by dtimeon          ###   ########.fr       */
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

	pos = file->error_data->bin_pos;
	if (pos >= 0)
		ft_printf("     Byte %lli: | {red}%08hhB{eoc} | <-- ", pos,
					*(file->champ_code + pos));
	ft_printf("{red}%s{eoc}\n\n", file->error_data->message);
}

void		print_asm_parsing_error(t_error_data *error_data)
{
	size_t	offset;
	size_t	line_num;
	char	*pos;
	size_t	tabs_num;
	size_t	i;

	if (error_data->line && error_data->line->initial_str)
	{
		line_num = error_data->line->num;
		offset = ft_printf("     line {blue}%u{eoc}: ", line_num);
		pos = error_data->asm_pos;
		if (pos)
			offset += pos - error_data->line->initial_str;
		else
			offset += ft_strlen(error_data->line->initial_str);
		ft_printf("{blue}%s{eoc}\n", error_data->line->initial_str);
		tabs_num = count_tabs(error_data->line->initial_str, pos);
		offset -= (tabs_num ? tabs_num + 4 : 0);
		i = 0;
		while (i++ < tabs_num)
			ft_printf("%c", '\t');
		ft_printf("{red}% *s{eoc}\n", offset, "^");
	}
	ft_printf("\t{red}%s{eoc}\n\n", error_data->message);
}

void		print_file_parsing_error(t_file *file)
{
	ft_printf("Parsing error in file {blue}%s{eoc}:\n", file->filename);
	if (file->is_assembly)
		print_asm_parsing_error(file->error_data);
	else
		print_bin_parsing_error(file);
	if (file->error_data->is_needed_to_free_message)
		ft_strdel(&(file->error_data->message));
}

void		print_usage(char *program_path)
{
	ft_printf("Usage: %s [-aw] [source.s binary.cor ... ]\n", program_path);
	ft_printf("\t-a: Instead of creating a .cor/.s file, outputs a stripped ");
	ft_printf("and annotated version of the code to the standard output\n");
	ft_printf("\t-w: Print syntax warnings for each file\n");
}
