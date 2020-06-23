/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_asm_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 00:45:24 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/26 07:54:09 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char				*find_label(char **str, t_file *file, t_line *line)
{
	char			*label_name;
	size_t			label_len;
	size_t			i;

	i = 0;
	while(((*str)[i] && ft_strchr(LABEL_CHARS, (*str)[i])))
		i++;
	if ((*str)[i] == LABEL_CHAR && i > 0)
	{
		label_len = i;
		label_name = ft_strnew(label_len);
		if (!label_name)
			exit_with_allocation_error(file->filename);
		ft_strncpy(label_name, *str, label_len);
		*str += label_len + 1;
		return(label_name);
	}
	else if (i == 0 && (*str)[i] == LABEL_CHAR)
		fill_error(file, line, *str - line->initial_str, 
					"Label name cannot be empty");
	return(NULL);
}

void				skip_non_useful_lines(t_line **line)
{
	while ((*line)->next && (is_blank_str((*line)->initial_str) ||
						is_comment((*line)->initial_str)))
		*line = (*line)->next;
}

unsigned char	is_name_cmd(char *start_pos)
{
	size_t		cmd_len;

	cmd_len = ft_strlen(NAME_CMD_STRING);
	return(ft_strnequ(start_pos, NAME_CMD_STRING, cmd_len));
}

unsigned char	is_comment_cmd(char *start_pos)
{
	size_t		cmd_len;

	cmd_len = ft_strlen(COMMENT_CMD_STRING);
	return(ft_strnequ(start_pos, COMMENT_CMD_STRING, cmd_len));
}
