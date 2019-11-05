/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:20:58 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/05 18:34:50 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	not NULL safety
*/
int		is_cor_extension(char *file_name)
{
	assert(file_name != NULL);
	char	*eol;

	eol = ft_strchr(file_name, '\0');
	return (!ft_strcmp(COR_EXTENSION, eol - 4));
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

int		check_octet(char c, UI octet)
{
	UI		a;
	UI		b;
	UI		i;
	size_t	char_size;
	size_t	ui_size;

	i = 0;
	char_size = 8 * sizeof(char);
	ui_size = 8 * sizeof(UI);
	while (char_size--)
	{
		a = c & (1 << i);
		b = COREWAR_EXEC_MAGIC & (1 << (i + ui_size - octet));
		if ((a > 0 && b == 0) || (a == 0 && b > 0))
			return (0);
		i++;
	}
	return (1);
}

/*
**	not NULL safety
*/
int		has_header(char *byte)
{
	assert(byte != NULL);
	if (check_octet(byte[0], 8)
	&& check_octet(byte[1], 16)
	&& check_octet(byte[2], 24)
	&& check_octet(byte[3], 32))
		return (1);
	return (0);
}
