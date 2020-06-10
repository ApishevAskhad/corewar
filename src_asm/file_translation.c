/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_translation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:45:40 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/10 09:47:12 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			make_output_filename(t_file *file)
{
	char		*dot_pos;
	char		*ext;
	int			diff;
	size_t		len;

	dot_pos = ft_strrchr(file->filename, '.');
	diff = ft_strlen(BINARY_EXTENSION) - ft_strlen(SOURCE_EXTENSION);
	if (file->is_assembly)
		ext = BINARY_EXTENSION;
	else
	{
		ext = SOURCE_EXTENSION;
		diff = -diff;
	}	
	len = ft_strlen(file->filename) + diff;
	file->out_filename = ft_strnew(len);
	if (!(file->out_filename))
		exit_with_allocation_error(file->filename);
	diff = dot_pos - file->filename;
	ft_strncpy(file->out_filename, file->filename, diff);
	ft_strncpy(file->out_filename + diff, ext, ft_strlen(ext));
}

unsigned char	create_output_file(t_file *file)
{
	make_output_filename(file);
	file->out_fd = open(file->out_filename, O_CREAT | O_TRUNC | O_WRONLY,
						S_IRWXU | S_IRWXG | S_IRWXO);
	return (file->out_fd > -1);
}

void			write_data_to_file(t_file *file)
{
	write(file->out_fd, file->header, file->header_size);
	write(file->out_fd, file->champ_code, file->code_size);
}

void			print_warnings(t_file *file)
{
	(void)file;
}

void				translate_file(t_file *file, short int options)
{
	unsigned char	is_file_created;

	fill_arg_types_codes(file->first_code_line);
	if (options & WARNINGS_OPTION_CODE)
		print_warnings(file);
	if (options & ANNOTATION_OPTION_CODE)
		print_annotated_file(file);
	else
	{
		if (file->is_assembly)
			translate_asm(file, options);
		else
			translate_bin(file, options);
		is_file_created = create_output_file(file);
		if (is_file_created)
		{
			write_data_to_file(file);
			ft_printf("Writing output program to %s\n", file->out_filename);
			close(file->out_fd);
		}
		else
			print_error(file->filename, "Couldn't create file to write output");	
	}
}
