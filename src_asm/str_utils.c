/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:46:09 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/11 02:09:02 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

unsigned char	is_not_blank_str(char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (1);
		str++;
	}
	return (0);
}

unsigned char	is_not_comment(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	if (*str && (*str == COMMENT_CHAR || *str == COMMENT_CHAR_2))
		return (0);
	return (1);
}
                                    