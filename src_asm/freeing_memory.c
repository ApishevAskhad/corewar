/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:44:01 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/16 01:08:54 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			delete_file(t_file **file)
{
	// TODO: free memory, allocated for args
	t_line		*temp_line;

	while ((*file)->first_line)
	{
		temp_line = (*file)->first_line;
		(*file)->first_line = temp_line->next;
		ft_strdel(&(temp_line->initial_str));
		ft_memdel((void**)&temp_line);
	}
	ft_memdel((void **)file);
}
