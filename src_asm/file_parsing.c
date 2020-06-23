/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:47:56 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/28 10:08:46 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		parse_binary_header(t_file *file)
{
	// TODO: parse binary header stored in file->binary_header
	(void)file;
}

static void		parse_header(t_file *file)
{
	if (file->is_assembly)
	{
		parse_asm_header(file);
		if (!(file->error_data) &&
			(!(file->champ_name) || !(file->champ_comment)))
		{
			fill_error(file, NULL, 0,
						"File should contain a champion name and a comment");
		}
	}
	else
		parse_binary_header(file);
}

static void		parse_binary_code(t_file *file)
{
	// TODO: parse binare data stored in file->champ_code
	(void)file;
}

static void		parse_code(t_file *file)
{
	if (file->is_assembly)
		parse_asm_code(file);
	else
		parse_binary_code(file);
}

void			parse_file(t_file *file)
{
	parse_header(file);
	if (!(file->error_data))
	{
		parse_code(file);
		if (!(file->error_data))
			file->is_correct = TRUE;
	}
}
