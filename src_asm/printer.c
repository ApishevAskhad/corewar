/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 19:08:08 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/29 14:07:36 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		print_error(char *filename, char *message)
{
	if (filename)
		ft_printf("Error in file \"%s\": %s\n", filename, message);
	else
		ft_printf("Error: %s\n", message);
}

static int	count_tabs(char *str)
{
	int		num_of_tabs;

	num_of_tabs = 0;
	while (*str)
	{
		if (*str == '\t')
			num_of_tabs++;
		str++;
	}
	return (num_of_tabs);
}

void		print_file_parsing_error(t_file *file)
{
	size_t	offset;
	size_t	line_num;
	size_t	pos;
	char	*message;

	ft_printf("Parsing error in file {blue}%s{eoc}:\n", file->filename);
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
	ft_printf("\t%s\n", message);
	if (file->error_data->is_needed_to_free_message)
		ft_strdel(&message);
}

void		print_usage(char *program_path)
{
	ft_printf("Usage: %s [-a] [source.s binary.cor ... ]\n", program_path);
	ft_printf("\t-a : Instead of creating a .cor/.s file, outputs a stripped ");
	ft_printf("and annotated version of the code to the standard output\n");
}
