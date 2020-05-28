/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 01:46:09 by dtimeon           #+#    #+#             */
/*   Updated: 2020/05/27 08:57:49 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char			*find_first_non_space_char(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	if (*str)
		return(str);
	return(NULL);
}

unsigned char	is_blank_str(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	if (*str)
		return (0);
	return (1);
}

unsigned char	is_comment(char *str)
{
	while (*str && ft_isspace(*str))
		str++;
	if (*str && (*str == COMMENT_CHAR || *str == COMMENT_CHAR_2))
		return (1);
	return (0);
}

char			*join_with_line_break(char *first_str, char *second_str)
{
	char		*dest;
	size_t		first_len;
	size_t		second_len;
	size_t		dest_len;

	first_len = ft_strlen(first_str);
	second_len = ft_strlen(second_str);
	dest_len = first_len + second_len + 1;
	dest = (char *)malloc(sizeof(char) * dest_len);
	if (!dest)
		return(NULL);
	ft_strncpy(dest, first_str, first_len);
	dest[first_len] = '\n';
	ft_strncpy(dest + first_len + 1, second_str, second_len);
	dest[dest_len] = '\0';
	return(dest);
}
                                    