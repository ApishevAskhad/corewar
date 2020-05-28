/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dealing_with_parsing_errors.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 00:56:31 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/26 10:58:10 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				fill_error(t_file *file, t_line *line,
								unsigned int pos, char *message)
{
	file->error_data = init_error_data(file->filename);
	file->error_data->line = line;
	file->error_data->error_pos = pos;
	file->error_data->message = message;
}
