/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_asm_header_saving_string.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:31:16 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/13 14:13:33 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_line	*find_str_end_line(t_line *cur_line, char *start_pos,
									size_t *str_len)
{
	char		*end_pos;

	while (!(end_pos = ft_strchr(start_pos, *STRING_END)))
	{
		*str_len += ft_strlen(start_pos) + 1;
		if (cur_line->next->initial_str)
			cur_line = cur_line->next;
		else
			return(NULL);
		start_pos = cur_line->initial_str;
	}
	*str_len += end_pos - start_pos;
	return(cur_line);
}

static char		*save_string_asm(t_file *file, t_line **cur_line,
									t_line *last_line, size_t str_len)
{
	char		*str;
	char		*start_pos;
	size_t		copied_len;
	size_t		last_line_str_len;

	if (!(str = ft_strnew(str_len)))
		exit_with_allocation_error(file->filename);
	copied_len = 0;
	start_pos = ft_strchr((*cur_line)->initial_str, *STRING_START) + 1;
	while (*cur_line != last_line)
	{
		ft_strcpy(str + copied_len, start_pos);
		copied_len += ft_strlen(start_pos);
		str[copied_len++] = '\n';
		*cur_line = (*cur_line)->next;
		start_pos = (*cur_line)->initial_str;
	}
	last_line_str_len = str_len - copied_len;
	ft_strncpy(str + copied_len, start_pos, last_line_str_len);
	start_pos += last_line_str_len + 1;
	if (!is_blank_str(start_pos) && !is_comment(start_pos))
		fill_warning(file, *cur_line,
						(t_pos)(find_first_non_space_char(start_pos) + 1), 
						"Unexpected symbol after the string end");
	return(str);
}

static void		check_end_of_string(t_file *file, t_line **cur_line,
								char *start_pos, unsigned char dest)
{
	size_t		max_len;
	size_t		str_len;
	t_line		*str_end_line;

	max_len = (dest == NAME ? PROG_NAME_LENGTH : COMMENT_LENGTH);
	str_len = 0;
	str_end_line = find_str_end_line(*cur_line, start_pos, &str_len);
	if (!str_end_line)
		fill_error(file, NULL, (t_pos)(char *)NULL,
			"Name and comment strings should end with " STRING_END " symbol");
	else if (str_len > max_len)
		fill_error(file, *cur_line, (t_pos)start_pos, "This string is too long");
	else
	{
		if ((dest == NAME) && !(file->champ_name))
			file->champ_name = save_string_asm(file, cur_line, str_end_line,
												str_len);
		else if ((dest == COMMENT) && !(file->champ_comment))
			file->champ_comment = save_string_asm(file, cur_line, str_end_line,
													str_len);
		else
			fill_error(file, NULL, (t_pos)(char *)NULL, 
					"File should have no more than one name and one comment");
	}
}

void			check_start_of_string(t_file *file, t_line **cur_line, 
										char *src, unsigned char dest)
{
	char		*start_pos;

	start_pos = find_first_non_space_char(src);
	if (start_pos && *start_pos == *STRING_START)
		check_end_of_string(file, cur_line, start_pos + 1, dest);
	else if (!start_pos)
		fill_error(file, *cur_line, (t_pos)(char *)NULL,
					"The string should start on this line");
	else
	{
		fill_error(file, *cur_line, (t_pos)start_pos,
				"Expected a string starting with a " STRING_START " symbol");
	}
	if (!(file->error_data))
	{
		*cur_line = (*cur_line)->next;
		skip_non_useful_lines(cur_line);
	}
}
