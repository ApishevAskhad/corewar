/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_binary_header.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 10:30:45 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/10 14:26:47 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned char	is_valid_magic(unsigned char *bin_data)
{
	if (*(t_magic *)(bin_data) != (t_magic)to_big_endian(COREWAR_EXEC_MAGIC, 
															sizeof(t_magic)))
		return (0);
	return (1);
}

static unsigned char	is_separators_present(unsigned char *bin_data)
{
	size_t				first_offset;
	size_t				second_offset;

	first_offset = sizeof(t_magic) + PROG_NAME_LENGTH;
	second_offset = first_offset + sizeof(t_sep) + sizeof(t_prog_size) + 
					COMMENT_LENGTH;
	if (*(t_sep *)(bin_data + first_offset) ||
			*(t_sep *)(bin_data + second_offset))
		return (0);
	return (1);
}

static unsigned char	is_header_structure_valid(unsigned char *bin_data,
													t_file *file)
{
	if (!is_valid_magic(bin_data))
	{
		fill_error(file, NULL, (t_pos)(ssize_t)-1, "Incorrect file signature");
		return (0);
	}
	else if (!is_separators_present(bin_data))
	{
		fill_error(file, NULL, (t_pos)(ssize_t)-1,
					"Zero-filled separator is not found");
		return (0);
	}
	return (1);
}

static unsigned char	is_code_size_correct(t_file *file)
{
	unsigned char		*code_size_pos;
	size_t				code_size_offset;

	code_size_offset = sizeof(t_magic) + PROG_NAME_LENGTH + sizeof(t_sep);
	code_size_pos = file->header + code_size_offset;
	if (*(t_prog_size *)code_size_pos != 
			(t_prog_size)to_big_endian(file->code_size, sizeof(t_prog_size)))
	{
		fill_error(file, NULL, (t_pos)(ssize_t)-1,
					"Declared program size does not match the actual size");
		return (0);
	}
	return (1);
}

void					parse_binary_header(t_file *file)
{
	unsigned char		*name_pos;
	unsigned char		*comment_pos;
	size_t				name_len;
	size_t				comment_len;
	size_t				comment_offset;

	if (is_header_structure_valid(file->header, file) &&
			is_code_size_correct(file))
	{
		name_pos = file->header + sizeof(t_magic);
		name_len = ft_strlen((char *)name_pos);
		file->champ_name = ft_strnew(name_len);
		if (!(file->champ_code))
			exit_with_allocation_error(file->filename);
		ft_strcpy(file->champ_name, (char *)name_pos);
		comment_offset = sizeof(t_sep) + PROG_NAME_LENGTH + sizeof(t_prog_size);
		comment_pos = name_pos + comment_offset;
		comment_len = ft_strlen((char *)comment_pos);
		file->champ_comment = ft_strnew(comment_len);
		if (!(file->champ_comment))
			exit_with_allocation_error(file->filename);
		ft_strcpy(file->champ_comment, (char *)comment_pos);
	}
}
