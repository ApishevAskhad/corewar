/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:20:58 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/05 18:42:33 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	not NULL safety
*/
int		is_cor_extension(char *file_name)
{
	assert(file_name != NULL);
	size_t	length;

	length = ft_strlen(file_name);
	if (length >= 4)
		return (!ft_strcmp(COR_EXTENSION, file_name + length - 4));
	return (0);
}

int		open_file(char *file_name)
{
	assert(file_name != NULL);
	int	fd;

	if (is_cor_extension(file_name))
	{
		if ((fd = open(file_name, O_RDONLY)) > 2)
			return (fd);
		else
			print_error("Can't read source file ", file_name);
	}
	return (0);
}

/*
**	not NULL safety
*/
int		has_header(char *byte)
{
	assert(byte != NULL);
	if (((COREWAR_EXEC_MAGIC & 0xFF000000) >> 24) == ((UI)byte[0] & 0xFF)
	&& ((COREWAR_EXEC_MAGIC & 0xFF0000) >> 16) == ((UI)byte[1] & 0xFF)
	&& ((COREWAR_EXEC_MAGIC & 0xFF00) >> 8) == ((UI)byte[2] & 0xFF)
	&& (COREWAR_EXEC_MAGIC & 0xFF) == ((UI)byte[3] & 0xFF))
		return (1);
	return (0);
}
