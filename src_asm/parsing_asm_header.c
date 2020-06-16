/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_asm_header.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 00:40:56 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/10 14:31:31 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void			find_name_or_comment(t_file *file, t_line **cur_line)
{
	char			*start_pos;
	unsigned char	dest;

	start_pos = find_first_non_space_char((*cur_line)->initial_str);
	if (is_name_cmd(start_pos))
	{
		dest = NAME;
		start_pos += ft_strlen(NAME_CMD_STRING);
	}
	else if (is_comment_cmd(start_pos))
	{
		dest = COMMENT;
		start_pos += ft_strlen(COMMENT_CMD_STRING);
	}
	else
		fill_error(file, *cur_line, (t_pos)NULL,
			"Expected champion name or comment at the beginning of the file");
	if (!(file->error_data))
		check_start_of_string(file, cur_line, start_pos, dest);
}

void				parse_asm_header(t_file *file)
{
	int				i;
	t_line			*cur_line;

	i = 0;
	cur_line = file->first_line;
	skip_non_useful_lines(&cur_line);
	if (!(cur_line))
		fill_error(file, NULL, (t_pos)NULL,
					"No champion name or comment found");
	while (i++ < 2 && !(file->error_data) && cur_line)
		find_name_or_comment(file, &cur_line);
	if (!(file->error_data))
		file->first_code_line = cur_line;
}
