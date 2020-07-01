/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 23:05:49 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/10 20:08:59 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

short int		read_options(char **args, int num_of_args, short int *options)
{
	int			i;
	char		*line;
	short int	cur_option;

	*options = 0;
	i = 0;
	while ((i < num_of_args) && (*args[i] == '-') && *(args[i] + 1))
	{
		line = args[i] + 1;
		cur_option = 0;
		while (*line)
		{
			if (!ft_strchr(OPTIONS_CHARS, *line))
				return (i);
			if (*line == ANNOTATION_OPTION)
				cur_option |= ANNOTATION_OPTION_CODE;
			if (*line == WARNINGS_OPTION)
				cur_option |= WARNINGS_OPTION_CODE;
			line++;
		}
		*options |= cur_option;
		i++;
	}
	return (i);
}
