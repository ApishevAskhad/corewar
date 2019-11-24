/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:05:49 by dtimeon           #+#    #+#             */
/*   Updated: 2019/11/20 00:28:16 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

short int		read_options(char *line)
{
	short int	options;

	if (*line != '-' || !*(line + 1))
		return (0);
	line++;
	options = 0;
	while (*line)
	{
		if (*line == ANNOTATION_OPTION)
			options |= ANNOTATION_OPTION_CODE;
		line++;
	}
	return (options);	
}
