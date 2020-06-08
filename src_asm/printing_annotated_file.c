/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing_annotated_file.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 13:42:34 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/08 15:18:40 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		print_strwise_row(t_line *line)
{
	int 		i;

	i = 0;
	ft_printf("%-7zu(%hd):\t    %-10s", line->pos, line->len,
				line->op_data->name);
	while (i < line->op_data->number_of_args)
	{
		ft_printf("%s%-*s", line->args[i].sym,
					18 - ft_strlen(line->args[i].sym), line->args[i].str_value);
		i++;
	}
	ft_printf("\n");
}

static void		print_bytewise_row(t_line *line)
{
	int 		i;
	int			j;
	int			value;

	ft_printf("%*s", 20, "");
	ft_printf("%-4hhd", line->op_data->op_code);
	if (line->op_data->has_arg_type_code)
		ft_printf("%-6hhu", line->arg_types_code);
	else
		ft_printf("      ");
	i = 0;
	while (i < line->op_data->number_of_args)
	{
		j = 0;
		value = to_big_endian(line->args[i].value, line->args[i].size);
		while (j < line->args[i].size)
		{
			ft_printf("%-4hhu", ((unsigned char *)&value)[j]);
			j++;
		}
		ft_printf("%-*s", 18 - (4 * line->args[i].size), "");
		i++;
	}
	ft_printf("\n");
}

static void		print_typewise_row(t_line *line)
{
	int 		i;

	ft_printf("%*s", 20, "");
				ft_printf("%-4hhd", line->op_data->op_code);
	if (line->op_data->has_arg_type_code)
		ft_printf("%-6hhu", line->arg_types_code);
	else
		ft_printf("      ");
	i = 0;
	while (i < line->op_data->number_of_args)
	{
		ft_printf("%-18d", line->args[i].value);
		i++;
	}
	ft_printf("\n");
}

static void		print_annotated_line(t_line *line)
{

	if (line->has_label_in)
		ft_printf("%-10zu:%12s:\n", line->pos, line->label->name);
	if (line->op_data)
	{
		print_strwise_row(line);
		print_bytewise_row(line);
		print_typewise_row(line);
		ft_printf("\n");
	}
}

void			print_annotated_file(t_file *file)
{
	t_line		*cur_line;

	ft_printf("File: %s\n", file->filename);
	ft_printf("Dumping annotated program on standard output\n");
	ft_printf("Program size: %zu bytes\n", file->code_size);
	ft_printf("Name: \"%s\"\n", file->champ_name);
	ft_printf("Comment: \"%s\"\n\n", file->champ_comment);
	cur_line = file->first_code_line;
	while (cur_line != file->last_line)
	{
		print_annotated_line(cur_line);
		cur_line = cur_line->next;
	}
}
