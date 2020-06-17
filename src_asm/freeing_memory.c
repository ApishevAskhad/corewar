/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:44:01 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/15 13:47:02 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			delete_lines(t_file *file)
{
	t_line		*temp_line;
	int			i;

	while (file->first_line)
	{
		temp_line = file->first_line;
		file->first_line = temp_line->next;
		ft_strdel(&(temp_line->initial_str));
		i = 0;
		if (temp_line->op_data)
			while (i < temp_line->op_data->number_of_args)
			{
				if (temp_line->args[i].str_value)
					ft_strdel(&(temp_line->args[i].str_value));
				i++;
			}
		ft_memdel((void**)&temp_line);
	}
}

void			delete_labels(t_label **labels)
{
	t_label		*temp_label;

	while (*labels)
	{
		temp_label = *labels;
		*labels = (*labels)->next;
		ft_strdel(&(temp_label->name));
		ft_memdel((void **)&temp_label);
	}
}

void			delete_warnings(t_file *file)
{
	t_warning	*temp_warning;

	temp_warning = file->first_warning;
	while (temp_warning)
	{
		file->first_warning = temp_warning->next;
		if (temp_warning->is_needed_to_free_message)
			ft_strdel(&temp_warning->message);
		ft_memdel((void **)&temp_warning);
		temp_warning = file->first_warning;
	}
}

void			delete_file(t_file **file)
{
	delete_lines(*file);
	if ((*file)->labels)
		delete_labels(&((*file)->labels));
	if ((*file)->error_data)
		ft_memdel((void **)&((*file)->error_data));
	if ((*file)->first_warning)
		delete_warnings(*file);
	if ((*file)->champ_name)
		ft_strdel(&((*file)->champ_name));
	if ((*file)->champ_comment)
		ft_strdel(&((*file)->champ_comment));
	if ((*file)->header)
		ft_memdel((void **)&((*file)->header));
	if ((*file)->champ_code)
		ft_memdel((void **)&((*file)->champ_code));
	if ((*file)->out_filename)
		ft_strdel(&(*file)->out_filename);
	ft_memdel((void **)file);
}
