/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_translation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:45:40 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/08 13:45:26 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			translate_file(t_file *file, short int options)
{
	fill_arg_types_codes(file->first_code_line);
	if (options & ANNOTATION_OPTION_CODE)
		print_annotated_file(file);
}
