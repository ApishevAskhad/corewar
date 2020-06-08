/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_asm_op_finding_op.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/28 10:00:33 by dtimeon           #+#    #+#             */
/*   Updated: 2020/06/07 17:25:57 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static unsigned char is_op_names_match(char *op_name, char *str,
										unsigned int op_len)
{
	if (ft_strnequ(op_name, str, op_len) && str[op_len] &&
			(!ft_isalpha(str[op_len]) || 
			str[op_len] == REG_CHAR ||
			str[op_len] == DIRECT_CHAR))
		return (TRUE);
	return (FALSE);
}

static t_op	 		*find_op(char **str, t_op *op_tab)
{
	int			 	i;

	i = 0;
	while (i < OP_NUM)
	{
		if (is_op_names_match(op_tab[i].name, *str, op_tab[i].name_len))
		{
			*str += op_tab[i].name_len;
			return(&((op_tab)[i]));
		}
		i++;
	}
	return(NULL);
}

t_op				*get_op(char **str)
{
	extern t_op		g_op_tab[OP_NUM];

	return(find_op(str, (t_op *)g_op_tab));
}

void				save_op_data(char **str, t_line *line)
{
	line->op_pos = *str - line->initial_str;
	line->op_data = get_op(str);
}
