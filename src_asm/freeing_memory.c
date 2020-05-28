/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:44:01 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/28 08:45:38 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


void			delete_lines(t_file *file)
{
	t_line		*temp_line;

	while (file->first_line)
	{
		temp_line = file->first_line;
		file->first_line = temp_line->next;
		ft_strdel(&(temp_line->initial_str));
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

void			delete_file(t_file **file)
{
	delete_lines(*file);
	if ((*file)->labels)
		delete_labels(&((*file)->labels));
	if ((*file)->error_data)
		ft_memdel((void **)&((*file)->error_data));
	if ((*file)->champ_name)
		ft_strdel(&((*file)->champ_name));
	if ((*file)->champ_comment)
		ft_strdel(&((*file)->champ_comment));
	ft_memdel((void **)file);
}
