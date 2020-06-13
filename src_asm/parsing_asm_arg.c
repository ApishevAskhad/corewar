/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_asm_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 09:52:03 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/13 14:12:09 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		assign_arg_as(unsigned char type, t_arg *arg,
							unsigned char is_dir_ind)
{
	if (type == T_REG)
	{
		arg->type = T_REG;
		arg->code = REG_CODE;
		arg->size = REG_CODE_SIZE;
		arg->sym = REG_SYM;
	}
	else if (type == T_IND)
	{
		arg->type = T_IND;
		arg->code = IND_CODE;
		arg->size = IND_CODE_SIZE;
		arg->sym = IND_SYM;
	}
	else if (type == T_DIR)
	{
		arg->type = T_DIR;
		arg->code = DIR_CODE;
		arg->size = (is_dir_ind ? DIR_AS_IND_CODE_SIZE : DIR_AS_DATA_CODE_SIZE);
		arg->sym = DIR_SYM;
	}
	arg->has_value_from_label = FALSE;
	arg->label_name = NULL;
	arg->value = 0;
	arg->str_value = NULL;
}

static void		save_label_arg_value(char **str, t_line *line, int i,
										t_file *file)
{
	int			j;

	j = 0;
	(*str)++;
	if (**str)
	{
		while ((*str)[j] && ft_strchr(LABEL_CHARS, (*str)[j]))
			j++;
		if (j > 0)
		{
			line->has_label_to_find = TRUE;
			line->args[i].has_value_from_label = TRUE;
			line->args[i].label_name = *str;
			line->args[i].label_name_len = j;
			line->args[i].str_value = ft_strndup(*str - 1, j + 1);
			*str += j;
		}
		else
			fill_error(file, line, (t_pos)*str,
						"Incorrect label name in this argument");
	}
	else
		fill_error(file, line, (t_pos)*str,
					"Unexpected line end, there should be a label name");
}

static void		save_arg_value(char **str, t_line *line, int i, t_file *file)
{
	int			j;

	j = 0;
	if (**str == '-')
		j++;
	while (ft_isdigit((*str)[j]))
		j++;
	if (j > 0)
	{
		line->args[i].value_len = j;
		line->args[i].value = ft_strtol(*str, NULL, 10);
		line->args[i].str_value = ft_strndup(*str, j);
		*str += j;
	}
	else
		fill_error(file, line, (t_pos)(*str + 1),
					"Incorrect value of the argument");
}

void			check_spaces_before_arg(char **str, t_line *line,
										t_file *file)
{
	char		*non_space_pos;

	non_space_pos = find_first_non_space_char(*str);
	if (non_space_pos && (non_space_pos == *str))
	{
		if (!ft_isspace(*(*str -1)) && *(*str - 1) != SEPARATOR_CHAR &&
			**str == REG_CHAR)
		{
			fill_warning(file, line, (t_pos)*str,
						"No space between operation and registry argument");
		}
		else if (!ft_isspace(*(*str -1)) && *(*str - 1) != SEPARATOR_CHAR &&
					ft_isdigit(**str))
		{
			fill_warning(file, line, (t_pos)*str,
						"No space between operation and indirect argument");
		}
	}
	*str = non_space_pos;
}

void			parse_asm_arg(char **str, t_line *line, int i, t_file *file)
{
	check_spaces_before_arg(str, line, file);
	line->args[i].pos = *str;
	if (*str && **str == REG_CHAR)
	{
		assign_arg_as(T_REG, &(line->args[i]), 0);
		(*str)++;
	}
	else if (*str && **str == DIRECT_CHAR)
	{
		assign_arg_as(T_DIR, &(line->args[i]), line->op_data->has_dir_as_ind);
		(*str)++;
	}
	else if (*str)
		assign_arg_as(T_IND, &(line->args[i]), 0);
	if (!(file->error_data))
	{
		if (*str && **str == LABEL_CHAR)
			save_label_arg_value(str, line, i, file);
		else if (*str && **str)
			save_arg_value(str, line, i, file);
		else
			fill_error(file, line, (t_pos)*str,
					"Unexpected line end, there should be the argument value");
	}
}
