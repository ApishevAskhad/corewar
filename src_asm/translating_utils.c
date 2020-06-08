/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translating_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 14:13:56 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/08 13:46:07 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void			fill_arg_types_codes(t_line *line)
{
	int			i;

	while (line->next)
	{
		if (line->op_data && line->op_data->has_arg_type_code)
		{
			i = 0;
			while (i < line->op_data->number_of_args)
			{
				line->arg_types_code |= (line->args[i].code << ((3 - i) * 2));
				i++;
			}
		}
		line = line->next;
	}
}

char			*ft_strndup(const char *src, size_t n)
{
	char		*dest;
	char		*temp_dest;

	if (!(dest = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	temp_dest = dest;
	while (*src && n--)
	{
		*temp_dest = *src;
		temp_dest++;
		src++;
	}
	*temp_dest = '\0';
	return (dest);
}

size_t			to_big_endian(size_t le_num, unsigned int size)
{
	int			len;
	int			i;
	size_t		be_num;

	len = size - 1;
	i = 0;
	be_num = 0;
	while (i <= len)
	{
		((unsigned char *)&be_num)[i] = ((unsigned char *)&le_num)[len - i];
		i++;
	}
	return (be_num);
}
