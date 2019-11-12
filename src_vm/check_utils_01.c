/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gloras-t <gloras-t@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 21:20:58 by gloras-t          #+#    #+#             */
/*   Updated: 2019/11/12 21:38:07 by gloras-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	not NULL safety
*/

int	is_cor_extension(char *file_name)
{
	assert(file_name != NULL);
	size_t	length;

	length = ft_strlen(file_name);
	if (length >= 4)
		return (!ft_strcmp(COR_EXTENSION, file_name + length - 4));
	return (0);
}
